#pragma once
#include <string>
#include "EndpointConfig.h"

class ParserConfig {
public:
    EndpointConfig parse(const std::string& filePayload); 
     //возвращает | имя метода |  принимает стринг с json-текстом

private:

};