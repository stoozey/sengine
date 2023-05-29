#ifndef SENGINE_ASSET_CREATOR_INVALID_TEMPLATE_HPP
#define SENGINE_ASSET_CREATOR_INVALID_TEMPLATE_HPP

#include "exceptions/exception.hpp"

namespace exceptions {
    class InvalidTemplate : public Exception {
    public:
        explicit InvalidTemplate(const std::string &message) : Exception(message) { };
    };
}

#endif //SENGINE_ASSET_CREATOR_INVALID_TEMPLATE_HPP