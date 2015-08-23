#!/bin/bash

cd execute && make clean && make
echo "/bin/echo hello world" | ./execute
cd ../my_fork && make clean && make
./my_fork 1000
cd ../iocmp && make clean && make
./iocmp 1 sampleInput.txt output.txt
./iocmp 2 sampleInput.txt output.txt
./iocmp 3 sampleInput.txt output.txt
echo "\n\nhw4 testing finishes succesfully."

