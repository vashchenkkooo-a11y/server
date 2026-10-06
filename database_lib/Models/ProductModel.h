#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

class ProductModel
{
public:
    ProductModel(const std::string &dbPath);
    void product_list();

private:
    SQLite::Database db;

};

// Получить список товаров из таблицы products для PRODUCT_LIST.
// Найти товар по id и узнать его название и остаток. Здесь «индекс товара» — это его id в базе.
// Уменьшить quantity после покупки, только если нужное количество есть.
