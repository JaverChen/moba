#include "ssl_wrapper.h"

SslWrapper::SslWrapper(boost::asio::io_context& io_context, const std::string& cert, const std::string& key) {
    ctx_ = SSL_CTX_new(TLS_server_method());
    SSL_CTX_use_certificate_file(ctx_, cert.c_str(), SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx_, key.c_str(), SSL_FILETYPE_PEM);
    ssl_ = SSL_new(ctx_);
}