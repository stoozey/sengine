#include <spdlog/spdlog.h>

#include "core/log.hpp"
#include "exceptions/exception.hpp"

namespace core {
    void Log::Info(const std::string &message) {
        return spdlog::info(message);
    }

    void Log::Warn(const std::string &message) {
        return spdlog::warn(message);
    }

    void Log::Error(const std::string &message) {
        throw exceptions::Exception(message);
    }

    void Log::Critical(const std::string &message) {
        spdlog::critical(message);
        exit(1);
    }
}