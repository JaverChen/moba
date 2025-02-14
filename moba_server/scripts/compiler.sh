sudo apt-get update && apt-get install -y   \
    build-essential  \
    cmake  \
    libboost-all-dev     \
    libmysqlclient-dev     \
    libhiredis-dev     \
    protobuf-compiler     \
    libprotobuf-dev

# 克隆 toml++ 仓库
git clone https://github.com/marzer/tomlplusplus.git
cd tomlplusplus

# 安装到系统目录
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
sudo make install

mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
sudo make install