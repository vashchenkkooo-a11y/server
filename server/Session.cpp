#include "Session.h"
#include <iostream>
#include <functional>
#include "Serializer.h"
#include "ParserRequest.h"
#include "UserDatabase.h"
#include "Request.h"

// Обслуживает одно TCP-соединение, т.е. читает запрос,
//  запускает его обработку и отправляет ответ

void Session::start() //
{
    // Создаётся дополнительный владелец текущей сессии, чтобы она жила, пока Boost ждёт запрос
    std::shared_ptr<Session> self = shared_from_this();
    socket_.async_read_some(               // жди, пока клиент что-нибудь отправит
        boost::asio::buffer(arr_, size),   // Полученные байты положи в arr_, максимально можно записать size байт
        std::bind(&Session::on_read,       // Когда чтение завершится, вызови on_read у объекта, который хранится в self
                  self,                    // удерживает сессию
                  std::placeholders::_1,   // ошибкa чтения
                  std::placeholders::_2)); // количество прочитанных байтов
}

void Session::on_read(const boost::system::error_code &error, // при ошибке выводит её, при успехе пишет сколько байт получили
                      std::size_t bytes)

{
    if (error)
    {
        std::cerr << "Ошибка чтения: " << error.message() << '\n';
        return;
    }

    std::string requestText(arr_, bytes); // Из буфера создаётся строка requestText. Берутся только реально полученные bytes,
    // а не все 2048 элементов.
    Parser parser;

    try
    {
        RegisterRequest request = parser.parseRequest(requestText); // jsin-строка превращается в C++-объект
        if ((request.event == "REGISTER" || request.event == "AUTH") &&
            (request.login.empty() || request.password.empty()))
        {
            throw std::invalid_argument(
                "логин и пароль не могут быть пустыми");
        }
        std::cout << "Получена команда: " << request.event << '\n';
        responseText_ = requestHandler_.handle(request); // Вот здесь Session передаёт запрос дальше,
        // Session не должна решать, правильный ли пароль: Полученный ответ сохраняется в responseText_
    }
    catch (const std::exception &e)
    {
        std::cerr << "Некорректный запрос клиента: " << e.what() << '\n';
        responseText_ = std::string("Некорректный запрос: ") + e.what();
    }

    boost::asio::async_write( // Асинхронно отправь через socket_ содержимое responseText_
        socket_,
        boost::asio::buffer(responseText_), // удерживает Session живой, просит после отправки вызвать on_write(error, bytes)
        std::bind(&Session::on_write,
                  shared_from_this(),
                  std::placeholders::_1,
                  std::placeholders::_2));
}
void Session::on_write(const boost::system::error_code &error, // Проверяет, удалось ли отправить ответ
                       std::size_t bytes)
{
    if (error)
    {
        std::cerr << "Ошибка отправки: " << error.message() << '\n';
        return;
    }
    ::Session::start();
}

// держать соедениение с сервером когда мы делаем команды
// дописать остальные хендлы