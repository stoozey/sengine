#ifndef SENGINE_ASSET_CREATOR_LOGGED_ERROR_HPP
#define SENGINE_ASSET_CREATOR_LOGGED_ERROR_HPP

#include "exceptions/exception.h"

namespace exceptions {
    class LoggedError : public Exception {
    public:
        LoggedError(const std::string &message) : Exception(message) { };
    };
}

#endif //SENGINE_ASSET_CREATOR_LOGGED_ERROR_HPP
