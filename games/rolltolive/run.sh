#!/bin/bash

# Test our game library, we PRELOAD the libs

P='../../lib/linux'

LD_LIBRARY_PATH="$P:$P/bullet/:$P/Irrlicht/" ./main
