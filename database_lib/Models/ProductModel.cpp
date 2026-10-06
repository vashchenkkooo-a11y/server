#include "ProductModel.h"
#include <iostream>
ProductModel::ProductModel(const std::string &dbPath) // ссылка на "db.db"
    : db(dbPath, SQLite::OPEN_READWRITE)
{
    db.exec(
        "CREATE TABLE IF NOT EXISTS products("
        "id_product INTEGER NOT NULL PRIMARY KEY,"
        "name_product TEXT NOT NULL,"
        "amount INTEGER NOT NULL"
        ")");
}
void ProductModel::product_list()
{
    SQLite::Statement ProductQuery(db, "SELECT * FROM products");
    while (ProductQuery.executeStep())
    {
        int id = ProductQuery.getColumn(0);
        std::string name = ProductQuery.getColumn(1);
        int amount = ProductQuery.getColumn(2);

        std::cout << id << " | " << name << " | " << amount << std::endl;
    }
}
