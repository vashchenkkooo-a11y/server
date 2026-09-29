//filePayload -> EndpointConfig
//Превращает текст EndpointConfig.json в объект EndpointConfig
#include "ParserConfig.h"
#include <stdexcept>
#include <boost/json.hpp> //объявления типов и функций из Boost.JSON

//Разбирает JSON настроек и получает объект config, в котором есть host и port





//filePayload - это std::string с JSON-текстом, надо передать 
//строку в функцию буст
//что возвращает|класс|имя метода | что принимает 
EndpointConfig ParserConfig::parse(const std::string& filePayload) {

//вызываем ф-ю буст.json, которая "разберет" текст:
boost::json::value parsedValue; // переменная
parsedValue = boost::json::parse(filePayload);

boost::json::object jsonObject; // переменная
jsonObject = parsedValue.as_object();

//достаём поля
// <объект>.<метод>(<ключ>) метод at()
boost::json::string hostBoost = jsonObject.at("host").as_string(); // найти в объекте значение  по ключу host и получаем его, делая boost.json string
const auto portValue = jsonObject.at("port").as_int64();
if (portValue < 1 || portValue > 65535)
    throw std::invalid_argument("Invalid port");
int port = static_cast<int>(portValue);

std::string host = hostBoost.c_str();

EndpointConfig config(
    host, port
 );

return config;   

}
