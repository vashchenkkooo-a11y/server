#pragma once
#include <string>

class FileReader {
public:
FileReader(std::string filePath);
std::string readFile();

private:
std::string filePath_;


};