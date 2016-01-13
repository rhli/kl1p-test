#!/bin/bash

# get current_dir
current_dir = pwd
# build project
sh ./examples/CompressedSensingExample/unix/UnixMakefile_x64Release_Make.sh
cd ./examples/CompressedSensingExample/unix/UnixMakefile_x64Release/
make
# return to home
cd $current_dir
