#ifndef SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
#define SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP

#include "exceptions/exception.hpp"

namespace exceptions {
    class NotImplemented : public Exception {
    public:
        explicit NotImplemented(const std::string &message = "") : Exception(fmt::format("Not yet implemented ({})", message)) { };
    };
}

#endif //SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
