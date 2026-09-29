#include "RequestHandler.h"
#include "TokenGenerator.h"
#include "Serializer.h"
#include <vector>

RequestHandler::RequestHandler(std::shared_ptr<UserDatabase> database)
    : database_(database)
{
}

std::string RequestHandler::handle(const RegisterRequest &request)
{
    if (request.event == "REGISTER")
        return handleRegister(request);

    if (request.event == "AUTH")
        return handleAuth(request);

    if (request.event == "PURCHASE_LIST")
        return handlePurchaseList(request);

    if (request.event == "PRODUCT_LIST")
        return handleProductList(request);

    if (request.event == "PURCHASE_CREATE")
        return handlePurchaseCreate(request);

    return "Неизвестная команда";
}

std::string RequestHandler::handleRegister(const RegisterRequest &request)
{
    if (database_->addUser(request.login, request.password))
    {
        database_->printUsers();
        return "Регистрация успешна";
    }

    return "Такой логин уже существует";
}

std::string RequestHandler::handleAuth(const RegisterRequest &request)
{
    if (database_->CheckCredentials(request.login, request.password)) // есть ли такой логин и совпадает ли пароль
    {
        TokenGenerator generator;
        std::string token = generator.generate();
        database_->saveToken(token, request.login);
        return token;
    }

    return "Неверный login или password";
}

std::string RequestHandler::handlePurchaseList(
    const RegisterRequest &request)
{
    std::vector<std::string> purchases;

    if (!database_->getPurchasesByToken(request.token, purchases))
        return "Неверный токен";

    if (purchases.empty())
        return "Список покупок пуст";

    std::string result = "Ваши покупки:\n";

    for (const std::string &purchase : purchases)
        result += "- " + purchase + '\n';

    return result;
}

std::string RequestHandler::handleProductList(
    const RegisterRequest &request)
{
    const std::map<int, Product> &products =
        database_->getProducts();

    std::string result = "Товары магазина:\n";
    for (const auto &product : products)
    {
        result += std::to_string(product.first) + ". " +
                  product.second.name +
                  ": осталось " +
                  std::to_string(product.second.quantity) +
                  "\n";
    }
    return result;
}

std::string RequestHandler::handlePurchaseCreate(const RegisterRequest &request)
{
    return database_->createPurchase(request.token,
        request.productId,
        request.quantity);
}

// в  RegisterRequest &request например:
// request.event = "REGISTER";
// request.login = "dio";
// request.password = "konodioda";