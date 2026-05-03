@echo off
if not exist build mkdir build
pushd build
cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE="Release"
cmake --build . --config Release
popd