#include "Log.h"

Log::LOGGER_PTR Log::s_CoreLogger;
Log::LOGGER_PTR Log::s_PluginLogger;
Log::LOGGER_PTR Log::s_ModuleLogger;

// 设置Logger
void Log::Init(){
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_CoreLogger = spdlog::stderr_logger_mt("Core");
    s_ModuleLogger = spdlog::stderr_logger_mt("Module");
    s_PluginLogger = spdlog::stderr_logger_mt("Plugin");

    spdlog::level::level_enum log_level = spdlog::level::off;

#ifdef LOG_LEVEL
    int lv = LOG_LEVEL;
    switch(lv){
        case 0:
            log_level = spdlog::level::trace;
            break;
        case 1:
            log_level = spdlog::level::info;
            break;
        case 2:
            log_level = spdlog::level::warn;
            break;
        case 3:
            log_level = spdlog::level::err;
            break;
        case 4:
            log_level = spdlog::level::critical;
            break;
        default:
            break;
    }
#endif

    s_CoreLogger->set_level(log_level);
    s_ModuleLogger->set_level(log_level);
    s_PluginLogger->set_level(log_level);
}
