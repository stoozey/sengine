#include "exceptions/exception.hpp"
#include "core/log.hpp"

namespace exceptions {
    Exception::Exception(const std::string &message) : std::logic_error(message) {
        core::Log::Error(message);
    }
}