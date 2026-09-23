#include "ParserRequest.h"
#include <boost/json.hpp>

// Метод класса Parser
// получает  джейсон-текст и создаёт из него объект RegisterRequest: например request.event = "register";
RegisterRequest Parser::parseRequest(const std::string &requestText)
// тип            Класс::его метод(джейсон-текст)
{
    // Разбираем джейсон-текст в объект
    boost::json::value parsedValue =
        boost::json::parse(requestText);

    boost::json::object jsonObject =
        parsedValue.as_object();

    RegisterRequest registerRequest;

    registerRequest.event =
        std::string(jsonObject.at("event").as_string());

    boost::json::object data =
        jsonObject.at("data").as_object();

    registerRequest.login =
        std::string(data.at("login").as_string());

    registerRequest.password =
        std::string(data.at("password").as_string());
    return registerRequest;
}