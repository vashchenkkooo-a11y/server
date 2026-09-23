//создаёт JSON-текст для отправки
#pragma once
#include <string>

class Serializer
{
public:
    // std::string serialize(const std::string& message);
    std::string serialize(const std::string& login, const std::string& password);
};
