# Justfile

# Compile and build the project
build:
    mkdir -p build
    g++ -std=c++17 -Iinclude src/main.cpp src/engine.cpp -o build/main

# Run the executable
run:
    ./build/main

# Clean build files
clean:
    rm -rf build
    rm -rf db/data/*
    rm -rf db/tables/*

#Rebuild
rebuild: clean
    mkdir -p build
    g++ -std=c++17 -Iinclude src/main.cpp src/engine.cpp -o build/main

