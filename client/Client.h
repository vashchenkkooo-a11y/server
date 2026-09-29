#pragma once
#include <boost/asio.hpp>
#include <string>

enum class Command
{
    Register,
    Auth,
    Buy,
    PurchaseList,
    ProductList,
    Exit,
    Unknown
};

class Client // представляет собой одного клиента 
{
public:
    using tcp = boost::asio::ip::tcp;
    using Endpoints = tcp::resolver::results_type; // хранятся адреса и порты, к которым клиент может подключиться

    Client(boost::asio::io_context& io_context, Endpoints endpoints); 

    void try_connect();

private:
    tcp::socket socket_;
    boost::asio::steady_timer timer_;
    Endpoints endpoints_;
    std::string token_;
    Command parseCommand(const std::string& command); //получить введённый текст и вернуть соответствующее значение Command

    void on_connect(const boost::system::error_code& error,
                    const tcp::endpoint& endpoint);

    void communicate(); //для общения с сервером после успешного подключения
    };
