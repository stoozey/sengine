#ifndef SENGINE_ASSET_CREATOR_INVALID_ARGUMENTS_HPP
#define SENGINE_ASSET_CREATOR_INVALID_ARGUMENTS_HPP

#include "exceptions/exception.hpp"

namespace exceptions {
    class InvalidArguments : public Exception {
    public:
        explicit InvalidArguments(const std::string &message) : Exception(message) { };
    };
}

#endif //SENGINE_ASSET_CREATOR_INVALID_ARGUMENTS_HPP