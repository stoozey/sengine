#include <fstream>
#include <iostream>

#include "utils/file_util.hpp"

namespace utils {
    size_t FileReadAllBytes(const std::string &filePath, char **out) {
        std::fstream stream;
        stream.open(filePath, std::ios::binary | std::ios::in);

        stream.seekg(0, std::ios::end);
        size_t length = stream.tellg();
        stream.seekg(0, std::ios::beg);

        char *buffer = new char[length];
        stream.read(buffer, length);

        *out = buffer;
        return length;
    }
}