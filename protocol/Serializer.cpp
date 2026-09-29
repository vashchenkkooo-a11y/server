#include "Serializer.h"
#include <boost/json.hpp>
//Делает JSON-запрос регистрации из логина и пароля




// std::string Serializer::serialize(const std::string& message)
// {
//     boost::json::object request; // Создаём пустой JSON-объект
//     request["message"] = message;

//     return boost::json::serialize(request); //превращаем объект в JSON-текст и возвращаем его
// }

std::string Serializer::serializeRegister(
    const std::string& login,
    const std::string& password)
    {
    boost::json::object data;
    data["login"] = login;
    data["password"] = password;


    boost::json::object request;
    request["event"] = "REGISTER";
    request["data"] = data;

    return boost::json::serialize(request); //возвращаем JSON-объект request как строку
}

std::string Serializer::serializeAuth(
    const std::string &login,
    const std::string &password)
{
    boost::json::object data;
    data["login"] = login;
    data["password"] = password;

    boost::json::object request;
    request["event"] = "AUTH";
    request["data"] = data;

    return boost::json::serialize(request);
}

std::string Serializer::serializePurchaseList(const std::string& token)
{
    boost::json::object data;
    data["token"] = token;

    boost::json::object request;
    request["event"] = "PURCHASE_LIST";
    request["data"] = data;

    return boost::json::serialize(request);
}

std::string Serializer::serializeProductList()
{
    boost::json::object data;

    boost::json::object request;
    request["event"] = "PRODUCT_LIST";
    request["data"] = data;

    return boost::json::serialize(request); //превращает C++-объект JSON в текст, который можно отправить серверу через сокет
}


std::string Serializer::serializePurchaseCreate(
    const std::string& token,
    int productId,
    int quantity)
{
    boost::json::object data;
    data["product_id"] = productId;
    data["quantity"] = quantity;

    boost::json::object request;
    request["event"] = "PURCHASE_CREATE";
    request["token"] = token;
    request["data"] = data;

    return boost::json::serialize(request);
}
// std::string Serializer::serializePurchaces(){}

//request — внешние скобки
// а data — внутренние, где лежат логин и пароль