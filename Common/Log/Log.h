#ifndef LOG_H
#define LOG_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Log{
    public:
        static void Init(int level = 1);

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetPluginLogger() { return s_PluginLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_PluginLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
};


#define CORE_TRACE(...)             ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)              ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)              ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)             ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_FATAL(...)             ::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define CLIENT_TRACE(...)           ::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...)            ::Log::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...)            ::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...)           ::Log::GetClientLogger()->error(__VA_ARGS__)
#define CLIENT_FATAL(...)           ::Log::GetClientLogger()->fatal(__VA_ARGS__)

#define PLUGIN_TRACE(...)           ::Log::GetPluginLogger()->trace(__VA_ARGS__)
#define PLUGIN_INFO(...)            ::Log::GetPluginLogger()->info(__VA_ARGS__)
#define PLUGIN_WARN(...)            ::Log::GetPluginLogger()->warn(__VA_ARGS__)
#define PLUGIN_ERROR(...)           ::Log::GetPluginLogger()->error(__VA_ARGS__)
#define PLUGIN_FATAL(...)           ::Log::GetPluginLogger()->fatal(__VA_ARGS__)

#endif
