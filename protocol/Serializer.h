// создаёт JSON-текст для отправки
#pragma once
#include <string>

class Serializer
{
public:
    // std::string serialize(const std::string& message);
    std::string serializeRegister(const std::string &login, const std::string &password);

    std::string serializeAuth(const std::string &login,
                              const std::string &password);

    std::string serializePurchaces(const std::string &token,
                                   const std::string &purchaces);

    std::string serializePurchaseList(const std::string &token);

    std::string serializeProductList();

    std::string serializePurchaseCreate(
    const std::string& token, int productId, int quantity);
};