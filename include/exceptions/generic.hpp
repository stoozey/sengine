#ifndef SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
#define SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP

#include <stdexcept>

namespace exceptions {
    class Generic : public std::logic_error {
    public:
        Generic(const std::string &message) : std::logic_error(message) { };
    };
}

#endif //SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
