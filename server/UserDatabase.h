#pragma once
#include <map> // std::map контейнер для хранения пар ключ -> значение
#include <string>

class UserDatabase
{
public:
    bool addUser(const std::string &login,
                 const std::string &password);
    void printUsers() const;

private:
    // база для всех объектов
    // Ключ login
    // Значение password

     std::map<std::string, std::string> users;
};