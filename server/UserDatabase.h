#pragma once
#include <map> // std::map контейнер для хранения пар ключ -> значение
#include <string>
#include <vector>

struct User
{
    std::string password;
    std::vector<std::string> purchases;
};


class UserDatabase
{
public:
    bool addUser(const std::string &login,
                 const std::string &password);
    void printUsers() const;

private:
    // база для всех объектов
    // Ключ login
    // Значение User

    std::map<std::string, User> users;
    std::map<std::string, std::string> tokenToLogin;
};