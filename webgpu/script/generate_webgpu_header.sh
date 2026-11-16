#!/usr/bin/env bash
set -euo pipefail

echo -e "#pragma once\n" > webgpu.hpp 

for f in  $(find . ! -name webgpu.hpp -name "*.hpp" | sed -e 's/^\.\///'); 
do 
	echo "#include \"webgpu/$f\"" >> webgpu.hpp;
done
