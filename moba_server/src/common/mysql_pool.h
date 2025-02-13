#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H

#include <mysql/mysql.h>
#include <string>

class DbConnector {
public:
    DbConnector(const std::string& host, const std::string& user, 
                const std::string& pass, const std::string& db);
    ~DbConnector();
    bool Execute(const std::string& query);

private:
    MYSQL* conn_;
};

#endif