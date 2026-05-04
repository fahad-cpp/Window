mkdir -p FSWindow/build
cd FSWindow/build
cmake -S .. -DCMAKE_BUILD_TYPE="Release"
cmake --build . --config Release
cd ../..
