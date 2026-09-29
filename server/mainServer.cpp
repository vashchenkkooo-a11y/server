// Читает адрес сервера из JSON и принимает подключения клиентов.
#include "FileReader.h"
#include "ParserConfig.h"
#include "Server.h"
#include <boost/asio.hpp>
#include <iostream>
#include "UserDatabase.h"

int main(int ac, char **av)
{

    std::shared_ptr<UserDatabase> database = std::make_shared<UserDatabase> ();

    try
    {
        if (ac != 2)
        {
            std::cerr << "Usage: server <config.json>\n";
            return 1;
        }

        FileReader reader(av[1]);
        std::string filePayload = reader.readFile();
        ParserConfig parser;
        EndpointConfig config = parser.parse(filePayload);

        std::cout << "host: " << config.host() << '\n';
        std::cout << "port: " << config.port() << '\n';

        boost::asio::io_context io_context;
        Server server(io_context, config, database); // БД передается в сервер - значит база общая для всего сервера, 
        //а не для дного запроса 
        io_context.run(); //программа начинает ждать подключения и сетевые сообщения
        std::cout << "Listening on " << config.host()
                  << " port " << config.port() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
