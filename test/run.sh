#!/bin/bash

# Test our game library, we need to PRELOAD the libs
# needs to be absolut path

PATH='/home/ryan/gameengine/lib/linux'

LD_LIBRARY_PATH="$PATH:$PATH/bullet/:$PATH/Irrlicht/" ./main
