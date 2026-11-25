#!/usr/bin/env python3

import argparse
from dataclasses import dataclass
from pathlib import Path

"""
Reads in texture files and creates a Rigel material file.

This should handle if the textures are in sRGB then it should convert them to linear.

This should be able to load .png files.

Each Rigel Material has the following:
  - albedo texture, if there is no texture then a single color for albedo
  - normal texture, if there is notexture then no normal map
  - roughness texture, if there is no texture then a single scalar for roughness
  - metallic texture, if there is no texture then a single scalar for metallic
  - emissive texture, if there is no texture then a single color for emissive
"""


def main():
    argument_parser = argparse.ArgumentParser(description="Rigel material processor.")

    albedo_group = argument_parser.add_mutually_exclusive_group(required=True)

    albedo_group.add_argument(
        "--albedo_path", type=Path, help="Path to albedo texture file."
    )

    albedo_group.add_argument(
        "--albedo_color", type=Path, help="Albedo RGB color [0, 1]."
    )

    argument_parser.add_argument(
        "--normal_path", type=Path, help="Path to normal texture file."
    )

    roughness_group = argument_parser.add_mutually_exclusive_group(required=True)

    roughness_group.add_argument(
        "--roughness_path", type=Path, help="Path to roughness texture file."
    )

    roughness_group.add_argument(
        "--roughness_scalar", type=Path, help="Roughness value [0, 1]."
    )

    metallic_group = argument_parser.add_mutually_exclusive_group(required=True)

    metallic_group.add_argument(
        "--metallic_path", type=Path, help="Path to metallic texture file."
    )

    metallic_group.add_argument(
        "--metallic_scalar", type=Path, help="Metallic value [0, 1]."
    )

    emissive_group = argument_parser.add_mutually_exclusive_group(required=True)

    emissive_group.add_argument(
        "--emissive_path", type=Path, help="Path to emissive texture file."
    )

    emissive_group.add_argument(
        "--emissive_color", type=Path, help="Emissive RGB color [0, 1]."
    )

    argument_parser.add_argument(
        "--output_material",
        required=True,
        type=Path,
        help="Path to output Rigel material file.",
    )

    arguments = argument_parser.parse_args()


if __name__ == "__main__":
    main()
