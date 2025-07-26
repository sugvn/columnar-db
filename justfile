# Justfile

# Compile and build the project
build:
    mkdir -p build
    g++ -std=c++17 -Iinclude src/*.cpp -o build/main

# Run the executable
run:
    ./build/main

# Clean build files
clean:
    rm -rf build
    rm -rf db/data/*
    rm db/tables/*

#Rebuild
rebuild:
    rm -rf build
    mkdir -p build
    g++ -std=c++17 -Iinclude src/main.cpp -o build/main

