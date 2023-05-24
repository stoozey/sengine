#ifndef SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP
#define SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP

#include "exceptions/exception.h"

namespace exceptions {
    class NotImplemented : public Exception {
    public:
        NotImplemented() : Exception("Not yet implemented") { };
    };
}

#endif //SENGINE_ASSET_CREATOR_NOT_IMPLEMENTED_HPP