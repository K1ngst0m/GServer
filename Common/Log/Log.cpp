#include "Log.h"

#include <memory>
#include <spdlog/sinks/stdout_sinks.h>

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_PluginLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

// 设置Logger
void Log::Init(int level){
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_CoreLogger = spdlog::stderr_logger_mt("Core");
    s_ClientLogger = spdlog::stderr_logger_mt("Client");
    s_PluginLogger = spdlog::stderr_logger_mt("Plugin");

    spdlog::level::level_enum log_level = spdlog::level::off;

    switch(level){
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

    s_CoreLogger->set_level(log_level);
    s_ClientLogger->set_level(log_level);
    s_PluginLogger->set_level(log_level);
}
