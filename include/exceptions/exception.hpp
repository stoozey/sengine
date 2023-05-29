#ifndef SENGINE_ASSET_CREATOR_EXCEPTION_H
#define SENGINE_ASSET_CREATOR_EXCEPTION_H

#include <stdexcept>

namespace exceptions {
    class Exception : public std::logic_error {
    public:
        Exception(const std::string &message);
    };
}

#endif //SENGINE_ASSET_CREATOR_EXCEPTION_H
