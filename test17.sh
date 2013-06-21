#!/bin/bash

make ex17
echo valgrind y/n?
read valgrind
if [ "$valgrind" = "y" ]; then
prefix="valgrind "
fi
echo Creating database with 10 rows...
$prefix ./bin/ex17 db.bat c 10 25

# echo Setting the first row...
# $prefix ./bin/ex17 db.bat s 1 zed zed@zedshaw.com

# echo Setting the second row...
# $prefix ./bin/ex17 db.bat s 2 joe joe@zedshaw.com

# echo Setting the third row...
# $prefix ./bin/ex17 db.bat s 3 tom tom@zedshaw.com

# echo Deleting the third row...
# $prefix ./bin/ex17 db.bat d 3

echo Cleaning up...
rm db.bat
