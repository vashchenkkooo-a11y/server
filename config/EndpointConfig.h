#pragma once
#include <set>
#include <string> 


//json 
// создать json  класса endpoint
// файлы в С++
// shared library (поверхностно)
// boost json 
// = 
// два новых класса в .h, который:
// 1 чтение файла (json) - input: file path, output: filepayloud 
// 2 класс парсинг json, запись в объект в endpointconfig   input:filepayloud, output: endpointconfig
class EndpointConfig {
public:
    // EndpointConfig(std::string host, 
    //     int port, int timeout_ms, std::string protocol); 
    EndpointConfig(std::string host, 
            int port);

        

        const std::string& host() const;
        
        int port() const;

        // int timeout_ms() const;
                                   
        // const std::string& protocol() const;

            
private:
std::string host_;
int port_;
// int timeout_ms_;
// std::string protocol_;
static std::set<std::string> allowed_protocols_;
};
