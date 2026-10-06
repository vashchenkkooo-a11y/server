#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

class UserModel
{
public:
    UserModel(const std::string &dbPath);

    bool reg(
        const std::string &login,
        const std::string &pass);

    std::string auth(
        const std::string &login,
        const std::string &pass);

    void saveToken(
        const std::string &token,
        const std::string &login);

    bool findLoginByToken(
        const std::string &token,
        std::string &login);

private:
    SQLite::Database const db;  
    int a;
    const int const *p = &a;
};                                                                                   

//дописать библиотеку (сделать свою библиотеку)
//сделать абстарктный виртуал класс один и чтобы он наследовался линейно, и чтобы dbpath было дискриптором и не создавались копии его
//должно быть многопоточным