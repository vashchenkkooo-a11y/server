#pragma once
#include <SQLiteCpp.h>
#include <string>
#include <vector>


class Product
{
public:
    int id;
    std::string name;
    int quantity;

private: 
    SQLite::Database &db; //модель не создаёт новую базу, а хранит доступ к уже открытому объекту
};

