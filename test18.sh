#!/bin/bash

set -e
make ex18
echo "Valgrind? 'y'"
read valgrind
if [ $valgrind = "y" ]; then
    prefix="valgrind "
    echo "Leak test? Y/N"
    read leak
    if [ $leak = "y" ]; then
	prefix="valgrind --leak-check=yes "
    fi
fi
$prefix ./bin/ex18 4 3 2 1 6 8
