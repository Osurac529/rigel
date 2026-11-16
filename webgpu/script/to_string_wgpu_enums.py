#!/usr/bin/env python3

#
# Run like this:
# C:\Users\miker\repos\rigel>python3 script\to_string_wgpu_enums.py --webgpu_header ..\..\wgpu\wgpu-windows-x86_64-msvc-debug\include\webgpu\webgpu.h --output_header include\graphics\enumeration_to_string.hpp --output_source src\graphics\enumeration_to_string.cpp
#

import argparse
from pathlib import Path

def skip_comment(stream):
    for line in stream:
        if "*/" in line:
            return
            
def parse_enumeration(stream, name:str, source_stream, header_stream):
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
    
    header_stream.write(f"std::ostream& operator<<(std::ostream& out, const {name} value);\n");
    source_stream.write(f"\n\nstd::ostream& operator<<(std::ostream& out, const {name} value) {{\n");
    source_stream.write("  return out << ToString(value);\n")
    source_stream.write("}\n");
        
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
    
    source_stream.write("#include \"graphics/enumeration_to_string.hpp\"\n\n")
    source_stream.write("#include <ostream>\n\n")
    
    with open(arguments.webgpu_header, "r", encoding="utf-8") as stream:
        for line in stream:
            if line.startswith("typedef enum"):                
                parse_enumeration(stream, line.split()[2], source_stream, header_stream)

main()