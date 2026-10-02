//таблицы:products   -> Показать товары, проверить и изменить остаток
#include "ProductModel.h"

SQLite::Statement query(db, "SELECT * FROM products");
