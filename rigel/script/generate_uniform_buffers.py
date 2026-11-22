#!/usr/bin/env python3

import argparse
import io
from pathlib import Path
from enum import Enum


class ParseError(Exception):
    pass


class TokenType(Enum):
    SYNTACTIC = 1
    ATTRIBUTE = 2
    KEYWORD = 3
    OTHER = 4


SYNTACTIC_TOKENS = [
    "&",
    "&&",
    "->",
    "@",
    "/",
    "!",
    "[",
    "]",
    "{",
    "}",
    ":",
    ",",
    "=",
    "==",
    "!=",
    ">",
    ">=",
    ">>",
    "<",
    "<=",
    "<<",
    "%",
    "-",
    "--",
    ".",
    "+",
    "++",
    "|",
    "||",
    "(",
    ")",
    ";",
    "*",
    "~",
    "_",
    "^",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "^=",
    ">>=",
    "<<=",
]

ATTRIBUTE_TOKENS = [
    "align",
    "binding",
    "builtin",
    "compute",
    "const",
    "diagnostic",
    "fragment",
    "group",
    "id",
    "interpolate",
    "invariant",
    "location",
    "blend_src",
    "must_use",
    "size",
    "vertex",
    "workgroup_size",
    "subgroup_size",
]

KEYWORD_TOKENS = [
    "alias",
    "break",
    "case",
    "const",
    "const_assert",
    "continue",
    "continuing",
    "default",
    "diagnostic",
    "discard",
    "else",
    "enable",
    "false",
    "fn",
    "for",
    "if",
    "let",
    "loop",
    "override",
    "requires",
    "return",
    "struct",
    "switch",
    "true",
    "var",
    "while",
]


def consume_block_comment(stream: io.TextIOBase):
    token: str = ""

    while True:
        char = stream.read()

        if not char:
            raise ParseError("Unexpected end of file.")

        if char.isspace():
            continue

        token += char

        if "*/" in token:
            return


def is_potential_syntatic(token: str) -> bool:
    for syntactic in SYNTACTIC_TOKENS:
        if syntactic.startswith(token):
            return True

    return False


def stream_to_characters(shader_path: Path):
    chars = []

    with open(shader_path, "r", encoding="utf-8") as stream:
        while True:
            char = stream.read(1)

            if not char:
                break

            chars.append(char)

    return chars


def get_token_type(token: str) -> TokenType:
    if token in ATTRIBUTE_TOKENS:
        return TokenType.ATTRIBUTE

    if token in KEYWORD_TOKENS:
        return TokenType.KEYWORD

    if token in SYNTACTIC_TOKENS:
        return TokenType.SYNTACTIC

    return TokenType.OTHER


def token_generator(shader_path: Path):
    chars = stream_to_characters(shader_path)
    index: int = 0
    line: int = 1
    token: str = ""

    while index < len(chars):
        char: str = chars[index]
        index += 1

        if char.isspace():
            if len(token) > 0:
                yield token, get_token_type(token)

                token = ""

            if "\n" == char:
                line += 1

            continue

        token += char

        if is_potential_syntatic(char):
            if len(token) > 1:
                if "_" == char:
                    continue

                token = token[:-1]

                yield token, get_token_type(token)

            token = char

            while is_potential_syntatic(token):
                char = chars[index]
                index += 1
                token += char

            if len(token) > 1:
                token = token[:-1]

            index -= 1
            yield token, TokenType.SYNTACTIC
            token = ""
        else:
            if 0 != len(token):
                if token in ATTRIBUTE_TOKENS:
                    yield token, TokenType.ATTRIBUTE
                    token = ""
                elif token in KEYWORD_TOKENS:
                    yield token, TokenType.KEYWORD
                    token = ""


def generate_uniform_buffers(shader_path: Path, output_directory: Path):
    output_directory.mkdir(exist_ok=True)

    generator = token_generator(shader_path)

    while True:
        try:
            token, type = next(generator)

            print(f'token: "{token}" type: {type}')
        except StopIteration:
            break


def main():
    argument_parser = argparse.ArgumentParser(
        description="Uniform buffer code generator."
    )

    argument_parser.add_argument(
        "--shader", required=True, type=Path, help="wgsl shader file path"
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