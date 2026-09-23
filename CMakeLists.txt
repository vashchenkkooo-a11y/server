cmake_minimum_required(VERSION 3.16)

project(mentorshipproject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost REQUIRED COMPONENTS json)
find_package(Threads REQUIRED)

# Копировать настройки рядом с собранными client и server.
configure_file(config/EndpointConfig.json EndpointConfig.json COPYONLY)

add_executable(client
    main/mainClient.cpp
    network/Client.cpp
    protocol/Serializer.cpp
    protocol/ParserRequest.cpp
    FileReader.cpp
    config/ParserConfig.cpp
    config/EndpointConfig.cpp
    network/UserDatabase.cpp
)

add_executable(server
    main/mainServer.cpp
    FileReader.cpp
    config/ParserConfig.cpp
    protocol/ParserRequest.cpp
    network/Server.cpp
    network/Session.cpp
    protocol/Serializer.cpp
    config/EndpointConfig.cpp
    network/UserDatabase.cpp
)

target_include_directories(client PRIVATE . config network protocol)
target_include_directories(server PRIVATE . config network protocol)

target_link_libraries(client PRIVATE Boost::json Threads::Threads)
target_link_libraries(server PRIVATE Boost::json Threads::Threads)
