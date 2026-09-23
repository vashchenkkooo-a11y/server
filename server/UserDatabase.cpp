#include "UserDatabase.h"
#include <iostream>
// база пользователей в static std::map: логин и пароль. Проверяет, занят ли логин.
// живёт одну сессию

bool UserDatabase::addUser(const std::string &login,
                           const std::string &password)
{
    if (users.find(login) != users.end()) // find(login) ищет логин в map,
        return false;

    users[login] = password; // пара ключ-значение
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
