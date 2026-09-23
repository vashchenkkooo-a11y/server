#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
// путь -> filePayload
FileReader::FileReader(std::string filePath) : filePath_(filePath) {}
//<тип_возврата> <ИмяКласса>::<ИмяМетода>(<аргументы>)
std::string FileReader:: readFile()
{
    std::ifstream file(filePath_);
    if (!file.is_open()) throw std::runtime_error("Cannot open file");

    std::stringstream buffer; 
    buffer << file.rdbuf();
    return buffer.str();

}