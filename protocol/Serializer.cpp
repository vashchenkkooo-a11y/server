#include "Serializer.h"
#include <boost/json.hpp>
//Делает JSON-запрос регистрации из логина и пароля




// std::string Serializer::serialize(const std::string& message)
// {
//     boost::json::object request; // Создаём пустой JSON-объект
//     request["message"] = message;

//     return boost::json::serialize(request); //превращаем объект в JSON-текст и возвращаем его
// }

std::string Serializer::serialize(
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

//request — внешние скобки
// а data — внутренние, где лежат логин и пароль