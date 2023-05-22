#ifndef SENGINE_LOG_HPP
#define SENGINE_LOG_HPP

#include <spdlog/spdlog.h>

namespace core {
    template<typename... Args>
    using format_string_t = fmt::format_string<Args...>;

    class Log {
    public:
        static void Info(const std::string &string) {
            spdlog::info(string);
        }

        static void Warn(const std::string &string) {
            spdlog::warn(string);
        }

        static void Error(const std::string &string) {
            spdlog::error(string);
            throw string.c_str();
        }

        static void Critial(const std::string &string) {
            spdlog::critical(string);
            exit(1);
        }

        template<typename... Args>
        static void Info(format_string_t<Args...> fmt, Args &&...args) {
            spdlog::info(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Warn(format_string_t<Args...> fmt, Args &&...args) {
            spdlog::warn(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Error(format_string_t<Args...> fmt, Args &&...args) {
            spdlog::error(fmt, std::forward<Args>(args)...);
            throw;
        }

        template<typename... Args>
        static void Critical(format_string_t<Args...> fmt, Args &&...args) {
            spdlog::critical(fmt, std::forward<Args>(args)...);
            exit(1);
        }
    };
}

#endif //SENGINE_LOG_HPP
