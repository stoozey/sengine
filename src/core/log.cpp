#include "core/log.hpp"

namespace core {
    void Log::Info(const std::string &message) {
        return Info("{}", message);
    }

    void Log::Warn(const std::string &message) {
        return Warn("{}", message);
    }

    void Log::Error(const std::string &message) {
        return Error("{}", message);
    }

    void Log::Critical(const std::string &message) {
        return Critical("{}", message);
    }
}