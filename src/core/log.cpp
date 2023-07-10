#include <easylogging++.h>

#include "core/log.hpp"
#include "exceptions/exception.hpp"

INITIALIZE_EASYLOGGINGPP

namespace core {
    void Log::Info(const std::string &message) {
        LOG(INFO) << message;
    }

    void Log::Warn(const std::string &message) {
        LOG(WARNING) << message;
    }

    void Log::Error(const std::string &message) {
        throw exceptions::Exception(message);
    }

    void Log::Critical(const std::string &message) {
        LOG(ERROR) << "CRITICAL - " << (message);
        exit(1);
    }
}