#!/bin/bash

rm -rf paraview
mkdir paraview

# Compile
g++ AdvNumerical.cpp
# run
./a.out