#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

class UserModel
{
public:
    UserModel(const std::string& databasePath);

    bool registerUser(
        const std::string& login,
        const std::string& password);

    bool authorizeUser(
        const std::string& login,
        const std::string& password);

private:
    SQLite::Database database_;
};