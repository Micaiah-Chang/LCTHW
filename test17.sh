#!/bin/bash

make ex17
echo valgrind y/n?
read valgrind
if [ "$valgrind" = "y" ]; then
prefix="valgrind "
fi
echo Creating database...
$prefix ./bin/ex17 db.bat c 10 25

echo Cleaning up...
rm db.bat
