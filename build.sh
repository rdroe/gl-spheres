
proj=$(pwd)
echo "project root: $proj"

pages_dir="$proj/docs"

cd build \
    && cmake -DCMAKE_TOOLCHAIN_FILE="/Users/robertroe/sites/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"  -DCMAKE_BUILD_TYPE=Debug $proj -G "Unix Makefiles" .. \
    && cmake --build . \
    && cp *.html $pages_dir \
    && cp *.wasm $pages_dir \
    && cp *.js $pages_dir \
    && cp *.data $pages_dir \
    && mv "$pages_dir/main.html" "$pages_dir/index.html" \
    && cd ..
