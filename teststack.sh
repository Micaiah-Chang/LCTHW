#!/bin/bash

set -e
make stack
echo "Valgrind? Y/N"
read valgrind
if [ "$valgrind" = "y" ]; then
prefix="valgrind --leak-check=yes "
fi
echo Sending dummy entries
$prefix ./bin/stack hello world

echo Done
