#!/bin/bash

rm -rf paraviewP
mkdir paraviewP

rm -rf paraviewU
mkdir paraviewU

rm -rf paraviewV
mkdir paraviewV

# Compile
g++ AdvNumerical.cpp
# run
./a.out