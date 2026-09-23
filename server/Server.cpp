#include "Server.h"
#include <functional>
#include <memory>
#include <utility>
#include <iostream>
#include <iostream>
#include "Session.h"

Server::Server(boost::asio::io_context &context, const EndpointConfig &config, std::shared_ptr<UserDatabase> database)
    : acceptor_(context, tcp::endpoint(boost::asio::ip::make_address(config.host()),
                                    config.port())), 
                                    statisticsTimer_(context),
                                    statusTimer_(context), database_(database)
{
    do_accept();
    start_statistics_timer();
    start_status_timer(); // первый запуск таймера
}

void Server::do_accept()
{
    acceptor_.async_accept(
        std::bind(&Server::on_accept, // Начни принимать одно подключение. Когда операция завершится - вызови on_accept
                  this,
                  std::placeholders::_1,
                  std::placeholders::_2));
}

void Server::start_statistics_timer()
{
    statisticsTimer_.expires_after(boost::asio::chrono::seconds(5));
    statisticsTimer_.async_wait(std::bind(
        &Server::on_statistics_timer, this));
}

void Server::on_statistics_timer()
{
    std::cout << " Всего подключено" << '\n' << acceptedClients_ << '\n' << "клиентов" << '\n';
    start_statistics_timer();
}

void Server::start_status_timer()
{
    statusTimer_.expires_after(
        boost::asio::chrono::seconds(10));

    statusTimer_.async_wait(
        std::bind(&Server::on_status_timer, this));
}

void Server::on_status_timer()
{
    std::cout << "Сервер работает" << '\n';

    start_status_timer();
}


void Server::on_accept(const boost::system::error_code &error, // Когда приём завершится, Asio вызовет обработчик
                       tcp::socket socket)
{
    if (error)
    {
        std::cerr << error.message() << '\n';
        return;
    }
    ++acceptedClients_;
    std::shared_ptr<Session> session =
        std::make_shared<Session>(std::move(socket), database_);
    session->start(); // Начать чтение от принятого клиента. (*session).start();
    do_accept();      // Начать ждать следующего клиента.
}
