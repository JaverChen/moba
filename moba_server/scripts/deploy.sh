sudo apt-get update
sudo apt-get install -y   \
    build-essential  \
    cmake  \
    libboost-all-dev     \
    libmysqlclient-dev     \
    libhiredis-dev     \
    protobuf-compiler     \
    libprotobuf-dev

#安装redis
sudo apt install redis-server

#使用 OpenSSL 工具生成自签名证书和私钥
# 创建证书存放目录
mkdir -p /etc/ssl/moba
cd /etc/ssl/moba
# 生成私钥（无密码）
openssl genrsa -out moba_gateway.key 2048
# 生成证书签名请求（CSR）
openssl req -new -key moba_gateway.key -out moba_gateway.csr \
  -subj "/C=CN/ST=Beijing/L=Beijing/O=Moba/CN=moba.gateway"
# 生成自签名证书（有效期 365 天）
openssl x509 -req -days 365 -in moba_gateway.csr -signkey moba_gateway.key -out moba_gateway.crt
# 清理 CSR 文件（可选）
rm moba_gateway.csr
#权限设置
chmod 644 /etc/ssl/moba/moba_gateway.crt  # 证书可读
chmod 600 /etc/ssl/moba/moba_gateway.key  # 私钥仅所有者可读

# 在当前项目根路径下

# 克隆 toml++ 仓库
git clone https://github.com/marzer/tomlplusplus.git
cd tomlplusplus
# 安装到系统目录
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
sudo make install