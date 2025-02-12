sudo apt-get update && apt-get install -y   \
    build-essential  \
    cmake  \
    libboost-all-dev     \
    libmysqlclient-dev     \
    libhiredis-dev     \
    protobuf-compiler     \
    libprotobuf-dev

mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
sudo make install