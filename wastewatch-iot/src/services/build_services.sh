#!/bin/bash

# Compile and build the program
g++ -o test_sender main.cpp lorawan_sender.cpp 

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
else
    echo "Compilation failed."
fi
