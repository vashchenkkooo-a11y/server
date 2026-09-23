#pragma once
//шаблон сетевого запроса
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
};