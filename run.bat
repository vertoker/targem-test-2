@echo off

rd /S /Q "build"
md "build"

g++ -O3 --std=c++11  "src/main.cpp" "src/String.h" "src/String.cpp" --output="build/executable.exe"

cd build
executable.exe
cd ..

@echo on