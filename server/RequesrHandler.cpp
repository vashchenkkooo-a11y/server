#include "RequestHandler.h"

RequestHandler::RequestHandler(std::shared_ptr<UserDatabase> database)
    : database_(database)
{}

std::string RequestHandler::handle(const RegisterRequest& request)
{
    if (request.event == "REGISTER")
    {
        return handleRegister(request);
    }

    return "Неизвестная команда";
}

std::string RequestHandler::handleRegister(const RegisterRequest& request)
{
    if (database_->addUser(request.login, request.password))
    {
        database_->printUsers();
        return "Регистрация успешна";
    }

    return "Такой логин уже существует";
}