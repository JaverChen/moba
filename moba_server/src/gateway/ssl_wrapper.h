#ifndef SSL_WRAPPER_H
#define SSL_WRAPPER_H

#include <openssl/ssl.h>
#include <boost/asio.hpp>

class SslWrapper {
public:
    SslWrapper(boost::asio::io_context& io_context, const std::string& cert, const std::string& key);
    SSL* GetSsl() { return ssl_; }

private:
    SSL_CTX* ctx_;
    SSL* ssl_;
};

#endif