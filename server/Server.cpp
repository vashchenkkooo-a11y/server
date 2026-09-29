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
    acceptor_.async_accept( // начни ждать подключение, а после завершения ожидания вызови переданный обработчик
        std::bind(&Server::on_accept, // Внутренний метод-обработчик результата.
        // его вызывает не сервер,  а буст асио, когда ожидание из do_accept() закончилось
                  this,
                  std::placeholders::_1,  //возможны два результата: 1) error есть → подключение не удалось;
                  std::placeholders::_2)); // 2) ошибки нет → socket содержит соединение с подключившимся клиентом.
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


void Server::on_accept(const boost::system::error_code &error, // это обработчик 
                       tcp::socket socket) 
{
    if (error)
    {
        std::cerr << error.message() << '\n';
        return; //прекращает выполнение on_accept
    }
    //Если ошибки нет:
    ++acceptedClients_;
    //создается сессия для подключившегося клиента:
    std::shared_ptr<Session> session = //записывается сюда полученный указатель
        std::make_shared<Session>(std::move(socket), database_); //std::make_shared<Session> создаёт в памяти объект класса Session
        //и возвращает shared_ptr на этот объект
        //передаем объекту Сессия сокет и БД
        //td::move(socket) передает владение сокетом
        //make_shared создает указатель + создаёт объект этого типа
        session->start(); // Начать чтение от принятого клиента. (*session).start();
    do_accept();      // Начать ждать следующего клиента.
}
