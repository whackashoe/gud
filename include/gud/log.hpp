#if !defined(GUD_LOG_H_INCLUDED_)
#define GUD_LOG_H_INCLUDED_

#include <gud/spdlog/spdlog.h>

namespace gud {

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

    static void set_level(spdlog::level::level_enum l);
    static void set_pattern(std::string const & pattern);

    template <typename T> static void trace(const T& v)
    {
        gud::log::logger->trace(v);
    }

    template <typename T> static void debug(const T& v)
    {
        gud::log::logger->debug(v);
    }

    template <typename T> static void info(const T& v)
    {
        gud::log::logger->info(v);
    }

    template <typename T> static void notice(const T& v)
    {
        gud::log::logger->notice(v);
    }

    template <typename T> static void warn(const T& v)
    {
        gud::log::logger->warn(v);
    }

    template <typename T> static void error(const T& v)
    {
        gud::log::logger->error(v);
    }

    template <typename T> static void critical(const T& v)
    {
        gud::log::logger->critical(v);
    }

    template <typename T> static void alert(const T& v)
    {
        gud::log::logger->alert(v);
    }

    template <typename T> static void emerg(const T& v)
    {
        gud::log::logger->emerg(v);
    }

    template <typename... Args> static void trace(const char* fmt, const Args&... args)
    {
        gud::log::logger->trace(fmt, args...);
    }

    template <typename... Args> static void debug(const char* fmt, const Args&... args)
    {
        gud::log::logger->debug(fmt, args...);
    }

    template <typename... Args> static void info(const char* fmt, const Args&... args)
    {
        gud::log::logger->info(fmt, args...);
    }

    template <typename... Args> static void notice(const char* fmt, const Args&... args)
    {
        gud::log::logger->notice(fmt, args...);
    }

    template <typename... Args> static void warn(const char* fmt, const Args&... args)
    {
        gud::log::logger->warn(fmt, args...);
    }

    template <typename... Args> static void error(const char* fmt, const Args&... args)
    {
        gud::log::logger->error(fmt, args...);
    }

    template <typename... Args> static void critical(const char* fmt, const Args&... args)
    {
        gud::log::logger->critical(fmt, args...);
    }

    template <typename... Args> static void alert(const char* fmt, const Args&... args)
    {
        gud::log::logger->alert(fmt, args...);
    }

    template <typename... Args> static void emerg(const char* fmt, const Args&... args)
    {
        gud::log::logger->emerg(fmt, args...);
    }
};

} /* /namespace gud */

#endif /* GUD_LOG_H_INCLUDED_ */
