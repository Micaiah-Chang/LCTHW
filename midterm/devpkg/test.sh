#!/bin/bash

set -e
sudo make install
sudo devpkg -S
sudo devpkg -I git://github.com/zedshaw/srpmin.git
sudo devpkg -B git://github.com/zedshaw/srpmin.git
sudo devpkg -F git://github.com/zedshaw/srpmin.git
sudo devpkg -L

