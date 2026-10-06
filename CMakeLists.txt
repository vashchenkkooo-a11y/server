cmake_minimum_required(VERSION 3.16)

project(mentorshipproject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost REQUIRED COMPONENTS json)
find_package(Threads REQUIRED)
find_package(SQLite3 REQUIRED)

# Копировать настройки рядом с собранными client и server.
configure_file(config/EndpointConfig.json EndpointConfig.json COPYONLY)
add_subdirectory(SQLiteCpp)
add_library(shop STATIC
    shop/Models/UserModel.cpp
    shop/TokenGenerator.cpp
)

target_include_directories(shop PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/shop
)

add_executable(client
    client/mainClient.cpp
    client/Client.cpp
    protocol/Serializer.cpp
    protocol/ParserRequest.cpp
    FileReader.cpp
    config/ParserConfig.cpp
    config/EndpointConfig.cpp
    server/UserDatabase.cpp
)

add_executable(server
    server/mainServer.cpp
    FileReader.cpp
    config/ParserConfig.cpp
    protocol/ParserRequest.cpp
    server/Server.cpp
    server/Session.cpp
    server/RequestHandler.cpp
    protocol/Serializer.cpp
    config/EndpointConfig.cpp
    server/UserDatabase.cpp
)

target_include_directories(client PRIVATE . config network protocol)
target_include_directories(server PRIVATE . config network protocol)

target_link_libraries(client PRIVATE Boost::json Threads::Threads)
target_link_libraries(server PRIVATE Boost::json Threads::Threads  SQLiteCpp shop)
target_link_libraries(shop PUBLIC SQLiteCpp PRIVATE Boost::headers
)