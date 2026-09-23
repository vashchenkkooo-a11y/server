#include "UserDatabase.h"
#include <iostream>

bool UserDatabase::addUser(const std::string &login,
                           const std::string &password)
{
    if (users.find(login) != users.end()) // find(login) ищет логин в map,
        return false;

    (users[login]).password = password; // пара ключ-значение
    return true;
}

void UserDatabase::printUsers() const
{
    std::cout << "Все пользователи:\n";

    for (const auto &user : users)
    {
        std::cout << "Логин: " << user.first << '\n';
    }
}
