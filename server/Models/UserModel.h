#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

class UserModel
{
public:
    UserModel(const std::string &dbPath);

    bool reg(
        const std::string &login,
        const std::string &pass);

    std::string auth(
        const std::string &login,
        const std::string &pass);

    void saveToken(
        const std::string &token,
        const std::string &login);

    bool findLoginByToken(
        const std::string &token,
        std::string &login);

private:
    SQLite::Database &db; //модель не создаёт новую базу, а хранит доступ к уже открытому объекту
};