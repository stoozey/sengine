#ifndef SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
#define SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP

#include <stdexcept>

namespace exceptions {
    class NotImplemented : public std::logic_error {
    public:
        NotImplemented() : std::logic_error("Not yet implemented") { };
    };
}

#endif //SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
