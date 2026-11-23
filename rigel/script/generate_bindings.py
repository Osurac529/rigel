#!/usr/bin/env python3

import argparse
from dataclasses import dataclass
from pathlib import Path
from enum import Enum

from wgsl_tokenizer import Token, TokenType, tokenize


class BindType(Enum):
    UNIFORM_BUFFER = 1
    TEXTURE_VIEW = 2
    SAMPLER = 3


class Visibility(Enum):
    VERTEX = 1
    FRAGMENT = 2
    COMPUTE = 3


class Binding:
    def __init__(self):
        self.name: str = None
        self.index: int = None
        self.bind_type: BindType = None
        self.visibility: set[Visibility] = set()


class Group:
    def __init__(self):
        self.index: int = None
        self.bindings: list[Binding] = []


def _is_in_attribute(tokens: list[Token], index: int, binding_name: str) -> bool:
    count: int = 0

    while index < len(tokens):
        token = tokens[index]
        index += 1

        if TokenType.SYNTACTIC == token.type and "{" == token.token:
            count = 1
            break

    while count > 0 and index < len(tokens):
        token = tokens[index]
        print(token)

        if TokenType.SYNTACTIC == token.type:
            if "{" == token.token:
                count += 1
                print("count up")
            elif "}" == token.token:
                count -= 1
                print("count down")
        elif TokenType.IDENTIFIER == token.type and binding_name == token.token:
            return True

        index += 1

    return False


def _parse_visibility(
    tokens: list[Token], index: int, binding_name: str
) -> set[Visibility]:
    visibility: set[Visibility] = set()

    while index < len(tokens):
        token = tokens[index]

        if TokenType.ATTRIBUTE == token.type:
            if "vertex" == token.token and _is_in_attribute(
                tokens, index, binding_name
            ):
                visibility.add(Visibility.VERTEX)
            elif "fragment" == token.token and _is_in_attribute(
                tokens, index, binding_name
            ):
                visibility.add(Visibility.FRAGMENT)
            elif "compute" == token.token and _is_in_attribute(
                tokens, index, binding_name
            ):
                visibility.add(Visibility.COMPUTE)

        index += 1

    return visibility


def _parse_binding(tokens: list[Token], index: int) -> tuple[Binding, int]:
    binding = Binding()
    index += 2
    binding.index = tokens[index].token

    while ";" != tokens[index].token:
        token = tokens[index]

        if TokenType.SYNTACTIC == token.type and ":" == token.token:
            binding.name = tokens[index - 1].token

            if "uniform" == tokens[index - 3].token:
                binding.bind_type = BindType.UNIFORM_BUFFER
            elif tokens[index + 1].token.startswith("texture_"):
                binding.bind_type = BindType.TEXTURE_VIEW
            elif tokens[index + 1].token == "sampler":
                binding.bind_type = BindType.SAMPLER

        index += 1

    binding.visibility = _parse_visibility(tokens, index, binding.name)

    return binding, index


def _parse_bindings(tokens: list[Token]) -> {int, Group}:
    num_tokens = len(tokens)
    index: int = 0
    groups: {int, Group} = {}
    group_index: int = None

    while index < num_tokens:
        token = tokens[index]

        if TokenType.ATTRIBUTE == token.type:
            if "group" == token.token:
                group_index = tokens[index + 2].token
                index += 2
            elif "binding" == token.token:
                binding, index = _parse_binding(tokens, index)

                if not group_index:
                    group_index = 0

                if group_index not in groups:
                    groups[group_index] = Group()
                    groups[group_index].index = group_index

                groups[group_index].bindings.append(binding)
                group_index = None

        index += 1

    return groups


def generate_bindings(shader_path: Path, output_directory: Path):
    output_directory.mkdir(exist_ok=True)

    groups = _parse_bindings(tokenize(shader_path))
    path = output_directory.joinpath(Path(shader_path.stem))
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
        header_stream.write(f"\nclass {shader_path.stem} {{\n")
        header_stream.write("public:")
        header_stream.write(
            f"\n  explicit {shader_path.stem}(const webgpu::Device& device);\n"
        )

        source_stream.write(f'#include "{header_path}"\n')
        source_stream.write("\nnamespace rigel::generated {\n")
        source_stream.write(
            f"\n{shader_path.stem}::{shader_path.stem}(const webgpu::Device& device):\n"
        )
        header_stream.write("private:\n")
        header_stream.write("  webgpu::Buffer buffer_;\n")
        header_stream.write("};\n")
        header_stream.write("\n} // namespace\n")

        source_stream.write("\n} // namespace\n")

    for key, value in groups.items():
        print(f"group index {value.index}")

        for binding in value.bindings:
            print("-" * 10)
            print(f"  binding name: {binding.name}")
            print(f"  binding index: {binding.index}")
            print(f"  binding type: {binding.bind_type}")
            print(f"  binding visibility: {binding.visibility}")


def main():
    argument_parser = argparse.ArgumentParser(
        description="WGSL Bindings code generator."
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

    generate_bindings(arguments.shader, arguments.output_directory)


if __name__ == "__main__":
    main()
