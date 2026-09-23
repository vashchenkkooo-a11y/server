// принимает новых клиентов

#pragma once
#include <boost/asio.hpp>
#include "EndpointConfig.h"
#include "ParserConfig.h"
#include "UserDatabase.h"
#include <memory>

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_context &context, const EndpointConfig &config, std::shared_ptr<UserDatabase> database);

private:
    tcp::acceptor acceptor_; // объект, который будет принимать подключения клиентов
    std::shared_ptr<UserDatabase> database_;

    void do_accept();        //  метод "начать ожидание"
    
    void on_accept(const boost::system::error_code &error,
                   tcp::socket socket); // обработать результат

    void on_write(const boost::system::error_code &error, std::size_t bytes);
    boost::asio::steady_timer statisticsTimer_;
    
    void start_statistics_timer();
    void on_statistics_timer();
    int acceptedClients_ = 0;
    boost::asio::steady_timer statusTimer_;
    void start_status_timer();
    void on_status_timer();
};
