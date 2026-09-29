#pragma once
// шаблон сетевого запроса
#include <string>

class Request
{
public:
    std::string event;
};

struct RegisterRequest : Request
{
    std::string login;
    std::string password;
    std::string token;
    int productId = 0;
    int quantity = 0;
};