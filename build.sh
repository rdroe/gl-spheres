
proj=$(pwd)
echo "project root: $proj"

cd build \
    && cmake -DCMAKE_TOOLCHAIN_FILE="/Users/robertroe/sites/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"  -DCMAKE_BUILD_TYPE=Debug $proj -G "Unix Makefiles" .. \
    && cmake --build . \
    && cp *.html ../pages \
    && cp *.wasm ../pages \
    && cp *.js ../pages \
    && cp *.data ../pages \
    && mv ../pages/main.html ../pages/index.html \
    && cd ..
