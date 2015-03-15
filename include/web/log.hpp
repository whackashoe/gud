#if !defined(WEB_LOG_H_INCLUDED_)
#define WEB_LOG_H_INCLUDED_

#include <web/spdlog/spdlog.h>

namespace web {

/**
 * Wrapper around spdlog
 */
class log
{
private:
    // our internal state / pointer to spdlog logging facility
    static std::shared_ptr<spdlog::logger> logger;

public:
    using level = spdlog::level::level_enum;

    static void set_level(spdlog::level::level_enum l)
    {
        web::log::logger->set_level(l);
    }

    template <typename T> static void trace(const T& v)
    {
        web::log::logger->trace(v);
    }

    template <typename T> static void debug(const T& v)
    {
        web::log::logger->debug(v);
    }

    template <typename T> static void info(const T& v)
    {
        web::log::logger->info(v);
    }

    template <typename T> static void notice(const T& v)
    {
        web::log::logger->notice(v);
    }

    template <typename T> static void warn(const T& v)
    {
        web::log::logger->warn(v);
    }

    template <typename T> static void error(const T& v)
    {
        web::log::logger->error(v);
    }

    template <typename T> static void critical(const T& v)
    {
        web::log::logger->critical(v);
    }

    template <typename T> static void alert(const T& v)
    {
        web::log::logger->alert(v);
    }

    template <typename T> static void emerg(const T& v)
    {
        web::log::logger->emerg(v);
    }

    template <typename... Args> static void trace(const char* fmt, const Args&... args)
    {
        web::log::logger->trace(fmt, args...);
    }

    template <typename... Args> static void debug(const char* fmt, const Args&... args)
    {
        web::log::logger->debug(fmt, args...);
    }

    template <typename... Args> static void info(const char* fmt, const Args&... args)
    {
        web::log::logger->info(fmt, args...);
    }

    template <typename... Args> static void notice(const char* fmt, const Args&... args)
    {
        web::log::logger->notice(fmt, args...);
    }

    template <typename... Args> static void warn(const char* fmt, const Args&... args)
    {
        web::log::logger->warn(fmt, args...);
    }

    template <typename... Args> static void error(const char* fmt, const Args&... args)
    {
        web::log::logger->error(fmt, args...);
    }

    template <typename... Args> static void critical(const char* fmt, const Args&... args)
    {
        web::log::logger->critical(fmt, args...);
    }

    template <typename... Args> static void alert(const char* fmt, const Args&... args)
    {
        web::log::logger->alert(fmt, args...);
    }

    template <typename... Args> static void emerg(const char* fmt, const Args&... args)
    {
        web::log::logger->emerg(fmt, args...);
    }
};

} /* /namespace web */

#endif /* WEB_LOG_H_INCLUDED_ */
