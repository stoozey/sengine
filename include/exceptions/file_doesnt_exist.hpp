#ifndef SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
#define SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP

#include "exceptions/exception.hpp"

namespace exceptions {
    class FileDoesntExist : public Exception {
    public:
        explicit FileDoesntExist(const std::string &filename) : Exception(filename) { };
    };
}

#endif //SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
