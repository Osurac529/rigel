#!/usr/bin/env python3

import argparse
from dataclasses import dataclass
from pathlib import Path

"""
Read in an obj or glb and convert it to a rigel mesh (.rm).

Each Rigel Mesh has the following attributes:
 - vertex buffer
   - position (required)
   - normal (optional)
   - tangent (optional)
   - texture coordinate (optional)
   For each attribute the format can be automatically chosen based on the range of values or explicitly set.
 - vertex buffer layout
 - index buffer
 - index buffer format (16/32 bit)
 - material ID
  - This will be a path to a file that holds the material data.
  - Material processing will be a separate script.
 - There will be a separate script that can join rigel meshes together that have like vertex buffer layouts but can have different material ids.
"""


def main():
    argument_parser = argparse.ArgumentParser(description="Rigel mesh processor.")

    argument_parser.add_argument(
        "--material",
        required=True,
        type=Path,
        help="Path to input Rigel material file.",
    )

    argument_parser.add_argument(
        "--input_mesh",
        required=True,
        type=Path,
        help="Path to non Rigal mesh file, such as obj or glb.",
    )

    argument_parser.add_argument(
        "--output_mesh",
        required=True,
        type=Path,
        help="Path to Rigel mesh .rm file.",
    )

    argument_parser.add_argument(
        "--position_format",
        choices=["auto", "f16", "f32", "unorm", "snorm"],
        default="f32",
        help="Format to use for position attribute.",
    )

    argument_parser.add_argument(
        "--normal_format",
        choices=["auto", "f16", "f32", "unorm", "snorm"],
        default="f32",
        help="Format to use for normal attribute.",
    )

    argument_parser.add_argument(
        "--tangent_format",
        choices=["auto", "f16", "f32", "unorm", "snorm"],
        default="f32",
        help="Format to use for tangent attribute.",
    )

    argument_parser.add_argument(
        "--texture_coordinate_format",
        choices=["auto", "f16", "f32", "unorm", "snorm"],
        default="f32",
        help="Format to use for texture coordinate attribute.",
    )

    arguments = argument_parser.parse_args()


if __name__ == "__main__":
    main()
