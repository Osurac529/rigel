#!/usr/bin/env bash
set -euo pipefail

echo -e "#pragma once\n" > graphics.hpp 

for f in  $(find . ! -name graphics.hpp -name "*.hpp" | sed -e 's/^\.\///'); 
do 
	echo "#include \"graphics2/$f\"" >> graphics.hpp;
done
