#include "Client.h"

#include <functional> // std::bind и std::placeholders
#include <iostream>
#include <string>
#include <utility> // std::move
#include "ParserRequest.h"
#include "Serializer.h"

// 1 консольное приложение со стороны клиента
// 2 опции : сервер, который содержит базу данных пользов магазина, запросы(свой протокол),  читать асинхр, чтоб не блокировал поток
//  один поток под соедин, второй - под консольный ввод

Client::Client(boost::asio::io_context &io_context, Endpoints endpoints)
    : socket_(io_context),
      timer_(io_context),
      endpoints_(std::move(endpoints))
{
}

void Client::try_connect()
{

    boost::asio::async_connect(
        socket_, endpoints_, // начни подключение и, когда станет известен результат, вызови on_connect
        std::bind(&Client::on_connect,
                  this,
                  std::placeholders::_1,
                  std::placeholders::_2));
}

void Client::on_connect(const boost::system::error_code &error,
                        const tcp::endpoint &endpoint)
{
    if (!error) // если подключились
    {
        std::cout << "Подключились к " << endpoint << '\n';
        communicate();
        return;
    }

    std::cerr << "Не удалось подключиться: " << error.message()
              << "\nПовтор через 3 секунды...\n";

    timer_.expires_after(boost::asio::chrono::seconds(3)); // если ошибка - таймер
    timer_.async_wait(
        std::bind(&Client::try_connect,
                  this));
}

void Client::communicate() 
{
    Serializer serializer; //для создания JSON-запросов

    while (true) //бесконечный цикл общения
    {
        std::string commandText;

        std::cout << "Введите команду: ";
        std::getline(std::cin, commandText);

        const Command command = parseCommand(commandText); //Преобразует строку в enum
        std::string requestText;

        switch (command) //выбирает нужный блок по команде
        {
        case Command::Register: //Оба случая используют общий код, потому что обе команды
        case Command::Auth: //запрашивают логин пароль
        {
            std::string login;
            std::string password;

            std::cout << "Login: ";
            std::getline(std::cin, login);

            std::cout << "Password: ";
            std::getline(std::cin, password);

            if (command == Command::Register)
                requestText = serializer.serializeRegister(login, password);
            else
                requestText = serializer.serializeAuth(login, password);

            break; //чтоб закончить именно этот кейс внутри свитча
        }

        case Command::PurchaseList:
        {
            if (token_.empty())
            {
                std::cout << "Сначала авторизуйтесь\n";
                continue;
            }
            requestText = serializer.serializePurchaseList(token_);
            break;
        }

        case Command::ProductList:
        {
            requestText = serializer.serializeProductList();
            break;
        }

        case Command::Buy:
        {
            if (token_.empty())
            {
                std::cout << "Сначала авторизуйтесь\n";
                continue;
            }

            std::string productId;
            std::string quantity;

            std::cout << "ID товара: ";
            std::getline(std::cin, productId);

            std::cout << "Количество: ";
            std::getline(std::cin, quantity);

            int id = std::stoi(productId);
            int count = std::stoi(quantity);


            requestText = serializer.serializePurchaseCreate(
                token_,
                id,
                count);

            break;
        }
        
    case Command::Exit:
        return;

    case Command::Unknown:
        std::cout << "Неизвестная команда\n";
        continue;
    }

    boost::asio::write(
        socket_,
        boost::asio::buffer(requestText));

    char arr[2048];
    const std::size_t bytes =
        socket_.read_some(boost::asio::buffer(arr));

    const std::string responseText(arr, bytes);
    if (command == Command::Auth)
    {
        if (responseText == "Неверный login или password")
        {
            token_.clear();
            std::cout << responseText << '\n';
        }
        else
        {
            token_ = responseText;
            std::cout << "Авторизация успешна. Токен: " << token_ << '\n';
        }
    }
    else
    {
        std::cout << responseText << '\n';
    }
}
}

Command Client::parseCommand(const std::string &command)
{
    if (command == "/REGISTER")
        return Command::Register;

    if (command == "/AUTH")
        return Command::Auth;

    if (command == "/BUY")
        return Command::Buy;

    if (command == "/PURCHASE_LIST")
        return Command::PurchaseList;

    if (command == "/PRODUCT_LIST")
        return Command::ProductList;

    if (command == "/EXIT")
        return Command::Exit;

    return Command::Unknown;
}