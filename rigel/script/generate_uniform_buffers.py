#!/usr/bin/env python3

import argparse
from dataclasses import dataclass
from pathlib import Path

from wgsl_tokenizer import Token, TokenType, tokenize


class ParseError(Exception):
    pass


@dataclass
class Field:
    name: str
    type: str


@dataclass
class DataTypeSizeAligment:
    size: int
    alignment: int


DATA_TYPES = {
    "f32": DataTypeSizeAligment(4, 4),
    "f16": DataTypeSizeAligment(4, 4),
    "i32": DataTypeSizeAligment(4, 4),
    "u32": DataTypeSizeAligment(4, 4),
    "vec2i": DataTypeSizeAligment(8, 8),
    "vec2u": DataTypeSizeAligment(8, 8),
    "vec2f": DataTypeSizeAligment(8, 8),
    "vec3i": DataTypeSizeAligment(12, 16),
    "vec3u": DataTypeSizeAligment(12, 16),
    "vec3f": DataTypeSizeAligment(12, 16),
    "vec4i": DataTypeSizeAligment(16, 16),
    "vec4u": DataTypeSizeAligment(16, 16),
    "vec4f": DataTypeSizeAligment(16, 16),
    "mat2x2f": DataTypeSizeAligment(16, 8),
    "mat4x4f": DataTypeSizeAligment(64, 16),
}


class Structure:
    def __init__(self, name: str):
        self.name: str = name
        self.fields: list[Field] = []

    def get_size(self) -> int:
        offset: int = 0
        max_alignment: int = 1

        for field in self.fields:
            data_type = DATA_TYPES.get(field.type)

            if offset % data_type.alignment != 0:
                offset += data_type.alignment - (offset % data_type.alignment)

            offset += data_type.size
            max_alignment = max(max_alignment, data_type.alignment)

        # The total struct size must be a multiple of the largest alignment member
        if offset % max_alignment != 0:
            offset += max_alignment - (offset % max_alignment)

        return offset

    def get_offset(self, field_name: str) -> int:
        offset: int = 0

        for field in self.fields:
            if field_name == field.name:
                return offset

            data_type = DATA_TYPES.get(field.type)

            if offset % data_type.alignment != 0:
                offset += data_type.alignment - (offset % data_type.alignment)

            offset += data_type.size

        raise ParseError(f"field name not found: {field_name}")


def parse_structure(tokens: list[Token], index: int) -> tuple[Structure, int]:
    structure = Structure(tokens[index].token)

    while index < len(tokens):
        token = tokens[index]

        if TokenType.SYNTACTIC == token.type and ":" == token.token:
            structure.fields.append(
                Field(tokens[index - 1].token, tokens[index + 1].token)
            )
        elif TokenType.SYNTACTIC == token.type and "}" == token.token:
            break

        index += 1

    return structure, index


def parse_structures(tokens: list[Token]) -> {str, Structure}:
    num_tokens = len(tokens)
    index: int = 0
    structures = {}

    while index < num_tokens:
        token = tokens[index]

        if TokenType.KEYWORD == token.type and "struct" == token.token:
            structures[tokens[index + 1].token], index = parse_structure(
                tokens, index + 1
            )

        index += 1

    return structures


def parse_uniforms(tokens: list[Token]) -> {str, Field}:
    num_tokens = len(tokens)
    index: int = 0
    uniforms = {}

    while index < num_tokens:
        token = tokens[index]

        if (
            TokenType.KEYWORD == token.type
            and "var" == token.token
            and "<" == tokens[index + 1].token
            and "uniform" == tokens[index + 2].token
        ):
            uniforms[tokens[index + 4].token] = Field(
                tokens[index + 4].token, tokens[index + 6].token
            )

        index += 1

    return uniforms


def generate_uniform_buffer(
    output_directory: Path,
    uniform: Field,
    structures: {str, Structure},
):
    path = output_directory.joinpath(Path(uniform.name))
    header_path = path.with_suffix(".hpp")
    source_path = path.with_suffix(".cpp")

    with (
        open(header_path, "w", encoding="utf-8") as header_stream,
        open(source_path, "w", encoding="utf-8") as source_stream,
    ):
        header_stream.write("#pragma once\n")
        header_stream.write('\n#include "rigel/math/math.hpp"\n')
        header_stream.write('#include "webgpu/webgpu.hpp"\n')
        header_stream.write("\nnamespace rigel::generated {\n")
        header_stream.write(f"\nclass {uniform.name} {{\n")
        header_stream.write("public:")
        header_stream.write(
            f"\n  explicit {uniform.name}(const webgpu::Device& device);\n"
        )
        header_stream.write(f"\n  {uniform.name}(const {uniform.name}&) = delete;\n")
        header_stream.write(
            f"  {uniform.name}& operator=(const {uniform.name}&) = delete;\n"
        )
        header_stream.write(f"  {uniform.name}({uniform.name}&&) = default;\n")
        header_stream.write(
            f"  {uniform.name}& operator=({uniform.name}&&) = default;\n"
        )

        source_stream.write(f'#include "{header_path}"\n')
        source_stream.write("\nnamespace rigel::generated {\n")
        source_stream.write(
            f"\n{uniform.name}::{uniform.name}(const webgpu::Device& device):\n"
        )

        if uniform.type in structures:
            structure = structures[uniform.type]

            source_stream.write(
                f"  buffer_(device.handle(), WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform, {structure.get_size()}) {{}}\n"
            )

            for field in structure.fields:
                header_stream.write(
                    f"\n  void {field.name}(const webgpu::Queue& queue, const {field.type}& value);\n"
                )

                source_stream.write(
                    f"\nvoid {uniform.name}::{field.name}(const webgpu::Queue& queue, const {field.type}& value) {{\n"
                )
                source_stream.write(
                    f"  queue.WriteBuffer(buffer_.handle(), value.data(), sizeof(value), {structure.get_offset(field.name)});\n"
                )
                source_stream.write("}\n")

        header_stream.write("private:\n")
        header_stream.write("  webgpu::Buffer buffer_;\n")
        header_stream.write("};\n")
        header_stream.write("\n} // namespace\n")

        source_stream.write("\n} // namespace\n")


def generate_uniform_buffers(shader_path: Path, output_directory: Path):
    output_directory.mkdir(exist_ok=True)

    tokens = tokenize(shader_path)

    structures = parse_structures(tokens)
    uniforms = parse_uniforms(tokens)

    for value in uniforms.values():
        generate_uniform_buffer(output_directory, value, structures)


def main():
    argument_parser = argparse.ArgumentParser(
        description="WGSL Uniform buffer code generator."
    )

    argument_parser.add_argument(
        "--shader", required=True, type=Path, help="WGSL shader file path"
    )

    argument_parser.add_argument(
        "--output_directory",
        required=True,
        type=Path,
        help="destination directory for generated code files",
    )

    arguments = argument_parser.parse_args()

    generate_uniform_buffers(arguments.shader, arguments.output_directory)


if __name__ == "__main__":
    main()
