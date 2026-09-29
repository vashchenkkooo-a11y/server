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

bool UserDatabase::CheckCredentials(const std::string &login, //правильные логин и пароль?
                                    const std::string &password)
{

    std::map<std::string, User>::const_iterator user = users.find(login);

    if (user == users.end())
        return false;
    return user->second.password == password; //
}

void UserDatabase::saveToken(const std::string &token, // записывает готовый токен в базу(не создает его!)
                             const std::string &login)
{
    tokenToLogin[token] = login;
}

bool UserDatabase::getPurchasesByToken(
    const std::string& token,
    std::vector<std::string>& purchases) //по ссылке, чтобы функция UserDatabase::getPurchasesByToken()
    //увидела сохранённые покупки
{
    auto tokenIt = tokenToLogin.find(token);
    if (tokenIt == tokenToLogin.end())
        return false;

    const std::string& login = tokenIt->second;

    auto userIt = users.find(login);
    if (userIt == users.end())
        return false;

    purchases = userIt->second.purchases;
    return true;
}

std::string UserDatabase::createPurchase(
    const std::string& token,
    int productId,
    int quantity)
{
    auto tokenIt = tokenToLogin.find(token);

    if (tokenIt == tokenToLogin.end())
        return "Неверный токен";

    auto productIt = products.find(productId);

    if (productIt == products.end() ||
        productIt->second.quantity < quantity)
    {
        return "Товара нет в наличии";
    }

    const std::string& login = tokenIt->second;

    auto userIt = users.find(login);

    if (userIt == users.end())
        return "Неверный токен";

    productIt->second.quantity -= quantity;

    userIt->second.purchases.push_back(
        productIt->second.name + " — " +
        std::to_string(quantity) + " шт.");

    return "Покупка создана";
}