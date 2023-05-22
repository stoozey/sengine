#ifndef SENGINE_ASSET_CREATOR_STRING_UTIL_HPP
#define SENGINE_ASSET_CREATOR_STRING_UTIL_HPP

#include <string>
#include <vector>

namespace utils {
    void StringVectorToCharVector(std::vector<const char *> *outVector, const std::vector<std::string> &stringVector);
    bool CompareStrings(const std::string &a, const std::string &b);
}

#endif //SENGINE_ASSET_CREATOR_STRING_UTIL_HPP
