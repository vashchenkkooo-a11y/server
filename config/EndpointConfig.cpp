#include "EndpointConfig.h" 
#include <stdexcept>
EndpointConfig::EndpointConfig(std::string host, 
        int port) : //, int timeout_ms, std::string protocol) 
        host_(host), 
        port_(port) {
        //timeout_ms_(timeout_ms),
        //protocol_(protocol) 
        
            if (port_ < 1 || port_ > 65535)
                throw (std::invalid_argument("Invalid port"));

            //if (allowed_protocols_.find(protocol_) == allowed_protocols_.end())
            //    throw (std::invalid_argument("Unsupported protocol"));
            //this -> port();
        }
        
        const std::string& EndpointConfig:: host() const {
            return host_; }
        
        int EndpointConfig:: port() const {
            return port_; }

        // int EndpointConfig:: timeout_ms() const {
        //     return timeout_ms_; }
                                   
        // const std::string& EndpointConfig:: protocol() const {
        //     return protocol_; }

