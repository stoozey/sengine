#ifndef SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
#define SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP

#include "exceptions/exception.hpp"

namespace exceptions {
    class Generic : public Exception {
    public:
        explicit Generic(const std::string &message) : Exception(message) { };
    };
}

#endif //SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
