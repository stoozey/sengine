#include "utils/string_util.hpp"

namespace utils {
    void StringVectorToCharVector(std::vector<const char *> *outVector, const std::vector<std::string> &stringVector) {
        outVector->clear();
        outVector->reserve(stringVector.size());

        for (const auto &i : stringVector) {
            outVector->push_back(i.c_str());
        }
    }

    bool CompareStrings(const std::string &a, const std::string &b) {
        return (a < b);
    }
}