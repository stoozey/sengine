#include <fstream>
#include <iostream>

#include "utils/file_util.h"

void FileReadAllBytes(const std::string &filePath, char *buffer) {
    std::fstream stream;
    stream.open(filePath, std::ios::in);

    stream.seekg(0, std::ios::end);
    size_t length = stream.tellg();
    stream.seekg(0, std::ios::beg);
    stream.read(buffer, length);
}