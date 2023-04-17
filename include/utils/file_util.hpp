#ifndef SENGINE_TEST1_FILE_UTIL_H
#define SENGINE_TEST1_FILE_UTIL_H

#include <string>

namespace utils {
    size_t FileReadAllBytes(const std::string &filePath, char **out);
}

#endif //SENGINE_TEST1_FILE_UTIL_H
