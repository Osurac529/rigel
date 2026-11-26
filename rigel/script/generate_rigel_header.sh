#!/usr/bin/env bash
set -euo pipefail

echo -e "#pragma once\n" > rigel.hpp 

for f in  $(find . ! -name rigel.hpp -name "*.hpp" | grep -v generated | sed -e 's/^\.\///'); 
do 
	echo "#include \"rigel/$f\"" >> rigel.hpp;
done
