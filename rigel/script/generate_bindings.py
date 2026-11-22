#!/usr/bin/env python3

import argparse
from dataclasses import dataclass
from pathlib import Path

from wgsl_tokenizer import Token, TokenType, tokenize


def generate_bindings(shader_path: Path, output_directory: Path):
    output_directory.mkdir(exist_ok=True)


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