#!/bin/bash

make ex17
echo valgrind y/n?
read valgrind
if [ "$valgrind" = "y" ]; then
	prefix="valgrind "
	echo "Advanced options? 1=Leak, 2=origins?"
	read options
	if [ options = 1 ]; then
		prefix="valgrind --leak-check=full "
	fi
	if [ options = 2 ];then
		prefix="valgrind --track-origins=yes "
	fi
fi

echo Creating database with 10 rows...
./bin/ex17 db.bat c 10 28

echo Setting the first row...
./bin/ex17 db.bat s 1 zed zed@zedshaw.com

echo Setting the second row...
./bin/ex17 db.bat s 2 joe joe@zedshaw.com

echo Setting the third row...
./bin/ex17 db.bat s 3 tom tom@zedshaw.com

echo Listing out everything...
./bin/ex17 db.bat l

echo Deleting the third row...
$prefix ./bin/ex17 db.bat d 3

echo Getting the second one...
$prefix ./bin/ex17 db.bat g 2

echo Cleaning up...
rm db.bat
