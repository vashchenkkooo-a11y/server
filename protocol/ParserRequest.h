#pragma once

#include <string>
#include "Request.h"

class Parser
{
public:
    RegisterRequest parseRequest(const std::string& requestText);
};