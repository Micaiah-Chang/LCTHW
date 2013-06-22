#!/bin/bash

make stack
echo "Valgrind? Y/N"
read valgrind
if [ "$valgrind" = "y" ]; then
prefix="valgrind --leak-check=yes "
fi
echo Sending dummy entries
$prefix ./bin/stack 2 3 5 4 6 8

echo Done
