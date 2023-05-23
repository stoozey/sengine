#ifndef SENGINE_ASSET_CREATOR_LOG_TPP
#define SENGINE_ASSET_CREATOR_LOG_TPP

#include "core/log.hpp"
#include "exceptions/logged_error.hpp"

namespace core {
    template <typename... T>
    std::string Log::GetFormattedMessage(fmt::format_string<T...> fmt, T&&... args) {
        return fmt::format(fmt, std::forward<T>(args)...);
    }

    template <typename... T>
    void Log::Info(fmt::format_string<T...> fmt, T&&... args) {
        std::string message = GetFormattedMessage(fmt, std::forward<T>(args)...);
        spdlog::info(message);
    }

    template <typename... T>
    void Log::Warn(fmt::format_string<T...> fmt, T&&... args) {
        std::string message = GetFormattedMessage(fmt, std::forward<T>(args)...);
        spdlog::warn(message);
    }

    template <typename... T>
    void Log::Error(fmt::format_string<T...> fmt, T&&... args) {
        std::string message = GetFormattedMessage(fmt, std::forward<T>(args)...);
        spdlog::error(message);
        throw exceptions::LoggedError(message);
    }

    template <typename... T>
    void Log::Critical(fmt::format_string<T...> fmt, T&&... args) {
        std::string message = GetFormattedMessage(fmt, std::forward<T>(args)...);
        spdlog::critical(message);
        exit(1);
    }
}

#endif //SENGINE_ASSET_CREATOR_LOG_TPP
