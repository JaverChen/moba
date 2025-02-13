#include "db_connector.h"

DbConnector::DbConnector(const std::string& host, const std::string& user,
                         const std::string& pass, const std::string& db) {
    conn_ = mysql_init(nullptr);
    mysql_real_connect(conn_, host.c_str(), user.c_str(), 
                      pass.c_str(), db.c_str(), 0, nullptr, 0);
}

DbConnector::~DbConnector() {
    mysql_close(conn_);
}

bool DbConnector::Execute(const std::string& query) {
    return mysql_query(conn_, query.c_str()) == 0;
}