// общается с одним уже подключённым клиентом
#pragma once
#include <boost/asio.hpp>
#include <string>
#include <memory>  // для shared_ptr и enable_shared_from_this
#include <utility> // для std::move.
#include <ctime>
#include "RequestHandler.h"

using boost::asio::ip::tcp;
void read(const boost::system::error_code &error,
          std::size_t bytes);

class Session : public std::enable_shared_from_this<Session>
{
public:
    
    Session(tcp::socket socket,
            std::shared_ptr<UserDatabase> database)
        : socket_(std::move(socket)), // принимает сокет и передаёт владение им полю socket_
          requestHandler_(database) {}

        void start();

    tcp::socket &socket()
    {
        return socket_;
    }

private:
    tcp::socket socket_;
    RequestHandler requestHandler_;
    char arr_[100];            // массив для входящих байтов
    std::string responseText_; // строка для ответа
    void on_read(const boost::system::error_code &error,
                 std::size_t bytes);
    void on_write(const boost::system::error_code &error, std::size_t bytes);
};
