#pragma once
#include <map> // std::map контейнер для хранения пар ключ -> значение
#include <string>
#include <vector>

struct User
{
    std::string password;
    std::vector<std::string> purchases;
};

struct Product
{
    std::string name;
    int quantity;
};

// struct Purchase
// {
//     std::string& uuid;
//     std::string productUuid;
//     int quantity;
// };

class UserDatabase
{
public:
    const std::map<int, Product> &getProducts() const
    {
        return products;
    }
    bool addUser(const std::string &login,
                 const std::string &password);
    void printUsers() const;

    bool CheckCredentials(const std::string &login,
                          const std::string &password);

    void saveToken(const std::string &token, // записывает готовый токен в базу(не создает его!)
                   const std::string &login);
    bool getPurchasesByToken(
        const std::string &token,
        std::vector<std::string> &purchases);
    std::string createPurchase(const std::string &token, int productIT, int quantity);


private:
    // база для всех объектов
    // Ключ login
    // Значение User

    std::map<std::string, User> users;
    std::map<std::string, std::string> tokenToLogin;

    std::map<int, Product> products{
        {1, {"Ошейник для бобика", 10}},
        {2, {"вкусняхи", 10}},
        {3, {"рыжий кот", 7}}};
};
// first  → ключ
// second → значение
//  first  → std::string, то есть login
//  second → User