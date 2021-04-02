#ifndef LOG_H
#define LOG_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

class Log{
    public:
        using LOGGER_PTR = std::shared_ptr<spdlog::logger>;

        static void Init(std::string lv = "0");

        inline static LOGGER_PTR &GetCoreLogger() { return s_CoreLogger; }
        inline static LOGGER_PTR &GetModuleLogger() { return s_ModuleLogger; }
        inline static LOGGER_PTR &GetPluginLogger() { return s_PluginLogger; }

    private:
        static LOGGER_PTR s_CoreLogger;
        static LOGGER_PTR s_PluginLogger;
        static LOGGER_PTR s_ModuleLogger;
};

#define CORE_TRACE(...)             ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)              ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)              ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)             ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_FATAL(...)             ::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define MODULE_TRACE(...)           ::Log::GetModuleLogger()->trace(__VA_ARGS__)
#define MODULE_INFO(...)            ::Log::GetModuleLogger()->info(__VA_ARGS__)
#define MODULE_WARN(...)            ::Log::GetModuleLogger()->warn(__VA_ARGS__)
#define MODULE_ERROR(...)           ::Log::GetModuleLogger()->error(__VA_ARGS__)
#define MODULE_FATAL(...)           ::Log::GetModuleLogger()->fatal(__VA_ARGS__)

#define PLUGIN_TRACE(...)           ::Log::GetPluginLogger()->trace(__VA_ARGS__)
#define PLUGIN_INFO(...)            ::Log::GetPluginLogger()->info(__VA_ARGS__)
#define PLUGIN_WARN(...)            ::Log::GetPluginLogger()->warn(__VA_ARGS__)
#define PLUGIN_ERROR(...)           ::Log::GetPluginLogger()->error(__VA_ARGS__)
#define PLUGIN_FATAL(...)           ::Log::GetPluginLogger()->fatal(__VA_ARGS__)

#endif
