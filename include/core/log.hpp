#ifndef SENGINE_LOG_HPP
#define SENGINE_LOG_HPP

#include <spdlog/spdlog.h>

namespace core {
    template<typename... Args>
    using format_string_t = fmt::format_string<Args...>;

    class Log {
    public:
        template<typename... Args>
        static void Info(format_string_t<Args...> fmt, Args &&...args) {
            spdlog::info(fmt, args...);
        }

        template<typename... Args>
        static void Warn(format_string_t<Args...> fmt, Args &&...args) {
            spdlog::warn(fmt, args...);
        }

        template<typename... Args>
        static void Error(format_string_t<Args...> fmt, Args &&...args) {
            spdlog::error(fmt, args...);
            throw;
        }

        template<typename... Args>
        static void Critical(format_string_t<Args...> fmt, Args &&...args) {
            spdlog::critical(fmt, args...);
            exit(1);
        }
    };
}

#endif //SENGINE_LOG_HPP
