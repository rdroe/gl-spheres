
proj=$(pwd)
echo "project root: $proj"

cd build \
    && cmake -DCMAKE_TOOLCHAIN_FILE="/Users/robertroe/sites/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"  -DCMAKE_BUILD_TYPE=Debug $proj -G "Unix Makefiles" .. \
    && cmake --build . \
    && cd ..
