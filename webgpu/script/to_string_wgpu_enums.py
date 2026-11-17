#!/usr/bin/env python3

#
# Run like this:
#mcaruso@Galactus:/mnt/c/users/miker/repos/rigel$ python3 webgpu/script/to_string_wgpu_enums.py --webgpu_header ../../wgpu/wgpu-windows-x86_64-msvc-debug/include/webgpu/webgpu.h --output_header webgpu/include/webgpu/enumeration_to_string.hpp --output_source webgpu/src/enumeration_to_string.cpp
#

import argparse
from pathlib import Path

def skip_comment(stream):
    for line in stream:
        if "*/" in line:
            return

def generate_stream_operator_impl(name:str, source_stream, header_stream):   
    header_stream.write(f"std::ostream& operator<<(std::ostream& out, const {name} value);\n");
    source_stream.write(f"\n\nstd::ostream& operator<<(std::ostream& out, const {name} value) {{\n");
    source_stream.write("  return out << webgpu::ToString(value);\n")
    source_stream.write("}\n");
            
def generate_to_string_impl(stream, name:str, source_stream, header_stream):
    header_stream.write(f"\nstd::string_view ToString(const {name} value);\n")
    source_stream.write(f"\nstd::string_view ToString(const {name} value) {{\n")
    source_stream.write(f"  switch(value) {{");
    
    done = False
    
    while not done:
        for line in stream:
            if '}' in line:
                done = True
                break
            elif "/*" in line:
                skip_comment(stream)
            else:
                source_stream.write(f"case {line.split()[0]}:\n")
                source_stream.write(f"  return \"{line.split()[0]}\";\n")
    source_stream.write("default:\n")
    source_stream.write("  throw std::invalid_argument(\"unknown enumeration value\");\n")
    source_stream.write("}\n")
    source_stream.write("}")   

def generate_stream_operator(webgpu_header:Path, source_stream, header_stream):
    with open(webgpu_header, "r", encoding="utf-8") as stream:
        for line in stream:
            if line.startswith("typedef enum"):                
                generate_stream_operator_impl(line.split()[2], source_stream, header_stream)

def generate_to_string(webgpu_header:Path, source_stream, header_stream):
    header_stream.write("namespace webgpu {\n")
    source_stream.write("namespace webgpu {\n")

    with open(webgpu_header, "r", encoding="utf-8") as stream:
        for line in stream:
            if line.startswith("typedef enum"):                
                generate_to_string_impl(stream, line.split()[2], source_stream, header_stream)

    header_stream.write("} // namespace webgpu\n")
    source_stream.write("} // namespace webgpu\n")

def main():
    argument_parser = argparse.ArgumentParser(description="Create to string for wgpu enumerations.")
    
    argument_parser.add_argument("--webgpu_header", type=Path, required=True, help="Path to the webgpu.h file")
    argument_parser.add_argument("--output_header", type=Path, required=True, help="Path to the generated header file for tostring/operator<< code.")
    argument_parser.add_argument("--output_source", type=Path, required=True, help="Path to the generated source file for tostring/operator<< code.")
    
    arguments = argument_parser.parse_args()
    
    header_stream = open(arguments.output_header, "w")
    source_stream = open(arguments.output_source, "w")

    header_stream.write("""#pragma once

#include <string_view>
#include <iosfwd>
#include <stdexcept>

#include <webgpu/wgpu.h>
""")
    
    source_stream.write("#include \"webgpu/enumeration_to_string.hpp\"\n\n")
    source_stream.write("#include <ostream>\n\n")

    generate_to_string(arguments.webgpu_header, source_stream, header_stream)
    generate_stream_operator(arguments.webgpu_header, source_stream, header_stream)


main()