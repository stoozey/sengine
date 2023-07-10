#ifndef SENGINE_LOG_HPP
#define SENGINE_LOG_HPP

#include <fmt/format.h>

namespace core {
    class Log {
    public:
        static void Info(const std::string &message);
        static void Warn(const std::string &message);
        static void Error(const std::string &message);
        static void Critical(const std::string &message);

        template <typename... T>
        static void Info(fmt::format_string<T...> fmt, T&&... args);

        template <typename... T>
        static void Warn(fmt::format_string<T...> fmt, T&&... args);

        template <typename... T>
        static void Error(fmt::format_string<T...> fmt, T&&... args);

        template <typename... T>
        static void Critical(fmt::format_string<T...> fmt, T&&... args);
    };
}

#include "core/log.tpp"
#endif //SENGINE_LOG_HPP
