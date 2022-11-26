#!/bin/bash

# Test our game library, we need to PRELOAD the libs
# needs to be absolut path

P='/home/rdh/Programs/C++/Project/lib/linux'

LD_LIBRARY_PATH="$P:$P/bullet/:$P/Irrlicht/" ./main
