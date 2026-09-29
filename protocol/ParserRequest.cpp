#include "ParserRequest.h"
#include <boost/json.hpp>

// Метод класса Parser
// получает  джейсон-текст и создаёт из него объект RegisterRequest: например request.event = "register";
RegisterRequest Parser::parseRequest(const std::string &requestText)
// тип            Класс::его метод(джейсон-текст)
{

    boost::json::value parsedValue =
        boost::json::parse(requestText);

    boost::json::object jsonObject =
        parsedValue.as_object();

    RegisterRequest registerRequest;

    registerRequest.event =
        std::string(jsonObject.at("event").as_string());

    boost::json::object data =
        jsonObject.at("data").as_object();

    if (registerRequest.event == "REGISTER" ||
        registerRequest.event == "AUTH")
    {
        registerRequest.login =
            std::string(data.at("login").as_string());

        registerRequest.password =
            std::string(data.at("password").as_string());
    }
    else if (registerRequest.event == "PURCHASE_LIST")
    {
        registerRequest.token =
            std::string(data.at("token").as_string());
    }
    else if (registerRequest.event == "PRODUCT_LIST")
    {
    }

    else if (registerRequest.event == "PURCHASE_CREATE")
    {
        registerRequest.token =  // чей запрос
            std::string(jsonObject.at("token").as_string());

        registerRequest.productId =
            static_cast<int>(data.at("product_id").as_int64());

        registerRequest.quantity =
            static_cast<int>(data.at("quantity").as_int64());
    }
    return registerRequest;
}