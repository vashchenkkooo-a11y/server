#include "UserModel.h"
#include "TokenGenerator.h"
// таблицы: users, tokens -> Регистрация, вход, сохранение токена, поиск пользователя по токену
UserModel::UserModel(const std::string &dbPath) //ссылка на "db.db"
    : db(dbPath, SQLite::OPEN_READWRITE) {}

    
void UserModel::saveToken(
    const std::string &token,
    const std::string &login)
{
    SQLite::Statement insertTokenQuery(db, "INSERT INTO tokens (token, login) VALUES (?, ?)");
    insertTokenQuery.bind(1, token);
    insertTokenQuery.bind(2, login);
    insertTokenQuery.exec();
}

std::string UserModel::auth(const std::string &login, const std::string &pass)
{
    SQLite::Statement findUserQuery(db, "SELECT * FROM users WHERE login = ?");
    findUserQuery.bind(1, login);

    if (findUserQuery.executeStep()) // попробуй получить найденную строку
    {
        const std::string db_pass = findUserQuery.getColumn(1).getText();
        if (pass == db_pass) {
            TokenGenerator generator;
            std::string token = generator.generate();

            saveToken(token, login);

            return token;
    }
}

    return "";
}

bool UserModel::reg(const std::string &login, const std::string &pass)
{
    SQLite::Statement checkLoginQuery(db, "SELECT * FROM users WHERE login = ?");
    checkLoginQuery.bind(1, login);
    if (checkLoginQuery.executeStep())
        return false;

    SQLite::Statement insertUserQuery(db, "INSERT INTO users (login, pass) VALUES (?, ?)");

    insertUserQuery.bind(1, login);
    insertUserQuery.bind(2, pass);
    insertUserQuery.exec(); // выполни подготовленный SQL-запрос, который изменяет базу данных

    return true;
}
