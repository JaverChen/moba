mkdir -p build && cd build
#打包时用 cmake -DCMAKE_BUILD_TYPE=Release ..
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j $(nproc)
sudo make install