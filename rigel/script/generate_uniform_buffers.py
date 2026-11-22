#!/usr/bin/env python3

import argparse
import re
from pathlib import Path
from enum import Enum
from collections.abc import Generator


class ParseError(Exception):
    pass


class TokenType(Enum):
    SYNTACTIC = 1
    ATTRIBUTE = 2
    KEYWORD = 3
    IDENTIFIER = 4
    LITERAL = 5


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

# These are from https://www.w3.org/TR/WGSL/#literal each regex is separated by a pipe
INT_LITERAL_REGEX = re.compile(r"^0[iu]?$|^[1-9][0-9]*[iu]?$|^0[xX][0-9a-fA-F]+[iu]?$")
FLOAT_LITERAL_REGEX = re.compile(
    r"^0[fh]$|[1-9][0-9]*[fh]$|^[0-9]*\.[0-9]+([eE][+-]?[0-9]+)?[fh]?$|^[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?[fh]?$|^[0-9]+[eE][+-]?[0-9]+[fh]?$"
)


def is_potential_syntatic(token: str) -> bool:
    for syntactic in SYNTACTIC_TOKENS:
        if syntactic.startswith(token):
            return True

    return False


def stream_to_characters(shader_path: Path) -> list[str]:
    chars = []

    with open(shader_path, "r", encoding="utf-8") as stream:
        while True:
            char = stream.read(1)

            if not char:
                break

            chars.append(char)

    return chars


def is_literal(token: str) -> bool:
    return (
        "true" == token
        or "false" == token
        or re.match(INT_LITERAL_REGEX, token)
        or re.match(FLOAT_LITERAL_REGEX, token)
    )


def get_token_type(token: str) -> TokenType:
    if is_literal(token):
        return TokenType.LITERAL

    if token in ATTRIBUTE_TOKENS:
        return TokenType.ATTRIBUTE

    if token in KEYWORD_TOKENS:
        return TokenType.KEYWORD

    if token in SYNTACTIC_TOKENS:
        return TokenType.SYNTACTIC

    return TokenType.IDENTIFIER


def token_generator(
    shader_path: Path,
) -> Generator[tuple[str, TokenType, int, int], None, None]:
    chars = stream_to_characters(shader_path)
    length = len(chars)
    index: int = 0
    line: int = 1
    line_index: int = index
    token: str = ""
    char: str = ""
    next_char: str = ""

    while index + 1 < length:
        char = chars[index]
        next_char = chars[index + 1]
        index += 1

        if char.isspace():
            if len(token) > 0:
                yield token, get_token_type(token), line, index - line_index
                token = ""

            if "\n" == char:
                line += 1
                line_index = index
        elif "/" == char and "/" == next_char:
            index += 1

            while index < length:
                char = chars[index]
                index += 1

                if "\n" == char:
                    line += 1
                    line_index = index
                    break
        elif "/" == char and "*" == next_char:
            count: int = 1
            index += 1

            # handle nested block comments
            while count > 0 and index + 1 < length:
                char = chars[index]
                next_char = chars[index + 1]
                index += 1

                if "/" == char and "*" == next_char:
                    count += 1
                elif "*" == char and "/" == next_char:
                    count -= 1
                elif "\n" == char:
                    line += 1
                    line_index = index

            index += 1
        else:
            token += char

            if is_potential_syntatic(char):
                if len(token) > 1:
                    if "_" == char or is_literal(token):
                        continue

                    token = token[:-1]

                    yield token, get_token_type(token), line, index - line_index

                token = char

                while index < length and is_potential_syntatic(token):
                    char = chars[index]
                    index += 1
                    token += char

                if len(token) > 1:
                    token = token[:-1]

                if index < length:
                    index -= 1

                yield token, TokenType.SYNTACTIC, line, index - line_index
                token = ""


def generate_uniform_buffers(shader_path: Path, output_directory: Path):
    output_directory.mkdir(exist_ok=True)

    generator = token_generator(shader_path)

    while True:
        try:
            token, type, line, line_index = next(generator)

            print(f'token: "{token}" type: {type} ln: {line} : ch: {line_index}')
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
