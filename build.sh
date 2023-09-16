echo "[DEBUG] cleaning old build..."
rm -rf build/*

echo "[DEBUG] creating new build..."
cd build || exit
cmake ..

echo "[DEBUG] build generated - compiling executable..."
make
./sfml-app