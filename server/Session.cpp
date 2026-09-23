#include "Session.h"
#include <iostream>
#include <functional>
#include "Serializer.h"
#include "ParserRequest.h"
#include "UserDatabase.h"
#include "Request.h"

// Обслуживает одно TCP-соединение, т.е. читает запрос,
//  запускает его обработку и отправляет ответ

void Session::on_read(const boost::system::error_code &error, // при ошибке выводит её, при успехе пишет сколько байт получили
                      std::size_t bytes)

{
    if (error)
    {
        std::cerr << "Ошибка чтения: " << error.message() << '\n';
        return;
    }

    std::string requestText(arr_, bytes);
    Parser parser;
    RegisterRequest request = parser.parseRequest(requestText);

    std::cout << "Получена команда: " << request.event << '\n';
    responseText_ = requestHandler_.handle(request);

    boost::asio::async_write(
        socket_,
        boost::asio::buffer(responseText_),
        std::bind(&Session::on_write,
                  shared_from_this(),
                  std::placeholders::_1,
                  std::placeholders::_2));
}
void Session::on_write(const boost::system::error_code &error,
                       std::size_t bytes)
{
    if (error)
        std::cerr << "Ошибка отправки: " << error.message() << '\n';
}
void Session::start()
{
    // self удерживает объект Session живым, пока ожидается чтение. Иначе функция start()
    // завершится, а сессия может исчезнуть до прихода данных
    std::shared_ptr<Session> self = shared_from_this();
    socket_.async_read_some( // когда из соединения придут данные запиши их в arr_, затем вызови on_read
        boost::asio::buffer(arr_),
        std::bind(&Session::on_read,
                  self, // удерживает сессию
                  std::placeholders::_1,
                  std::placeholders::_2));
}
