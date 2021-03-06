#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>


Log::LOGGER_PTR Log::s_CoreLogger;
Log::LOGGER_PTR Log::s_PluginLogger;
Log::LOGGER_PTR Log::s_ModuleLogger;

// 设置Logger
void Log::Init(std::string lv) {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_CoreLogger = spdlog::stderr_color_mt("Core");
    s_ModuleLogger = spdlog::stderr_color_mt("Module");
    s_PluginLogger = spdlog::stderr_color_mt("Plugin");

    spdlog::level::level_enum log_level = spdlog::level::off;

    switch (lv[0]) {
        case '0':
            log_level = spdlog::level::trace;
            break;
        case '1':
            log_level = spdlog::level::info;
            break;
        case '2':
            log_level = spdlog::level::warn;
            break;
        case '3':
            log_level = spdlog::level::err;
            break;
        case '4':
            log_level = spdlog::level::critical;
            break;
        default:
            break;
    }

    s_CoreLogger->set_level(log_level);
    s_ModuleLogger->set_level(log_level);
    s_PluginLogger->set_level(log_level);
}
