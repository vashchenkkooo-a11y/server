#pragma once
#include <memory>
#include <string>

#include "Request.h"
#include "UserDatabase.h"

class RequestHandler //класс, который обрабатывает команды
{
public:
    RequestHandler(std::shared_ptr<UserDatabase> database);

    std::string handle(const RegisterRequest& request); //принимает запрос(реквест) и понять чо с ним делать
private:
    std::shared_ptr<UserDatabase> database_;

    std::string handleRegister(const RegisterRequest& request); //обработчик регистера
}; //в request лежат данные, которые клиент прислал серверу