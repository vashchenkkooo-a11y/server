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
    std::string command;
    std::cout << "Введите команду: ";
    std::getline(std::cin, command);

    Serializer serializer;
    std::string requestText;
    RegisterRequest registerRequest;
    

    if (command == "/REGISTER")
    {
        std::string login;
        std::string password;

        std::cout << "Login: ";
        std::getline(std::cin, login);

        std::cout << "Password: ";
        std::getline(std::cin, password);

        requestText = serializer.serialize(login, password);//поклали джейсон-текст в переменную
    }
    else
    {
        std::cout << "Неизвестная команда\n";
        return;
    }
    boost::asio::write(socket_, boost::asio::buffer(requestText)); // клиент отправляет содержимое requestText по этому соединению

    char arr[100];
    const std::size_t bytes = socket_.read_some(boost::asio::buffer(arr));
    std::string responseText(arr, bytes);

    std::cout << responseText << '\n';
}
