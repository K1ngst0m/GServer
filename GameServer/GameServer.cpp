//
// Created by npchitman on 3/18/21.
//

#include "pch.h"
#include "PluginManager.h"
#include <Log/Log.h>
#include <thread>
#include <chrono>

// 入口
int main(int argc, char** argv){
    const char *pluginName = "";

#if 0 // 参数设置插件名
    // 系统运行参数为插件名
    if (argc > 1){
        pluginName = argv[1];
    }
#else // 参数设置日志优先级

    int log_level = 0;
    std::string arg = argv[1];
    try{
        std::size_t pos;
        log_level = std::stoi(arg, &pos);
        if(pos < arg.size()){
            CORE_ERROR("Trailing characters after number: {}", arg);
        }
    }
    catch (std::invalid_argument const &ex) {
        CORE_ERROR("Invalid number", arg);
    }
    catch (std::out_of_range const &ex) {
        CORE_ERROR("Number out of range", arg);
    }

    if(log_level > 4) log_level = 4;
    if(log_level < 0) log_level = 0;

#endif

    Log::Init(log_level);

    CORE_INFO("Server start");

    // 初始化插件
    CORE_INFO("Plugin Load");
    auto * pluginManager = new PluginManager(pluginName);
    if(!pluginManager->LoadPlugin()){
        return -1;
    }

    CORE_INFO("Plugin Init");
    if(!pluginManager->Init()){
        CORE_ERROR("Plugin init failed");
        return -1;
    }

    CORE_INFO("Plugin Update");
    while(true){
        CORE_TRACE("(trace) plugin updating");
//        CORE_INFO("(info) plugin updating");
//        CORE_WARN("(warn) plugin updating");
//        CORE_ERROR("(error) plugin updating");

        // 插件运行
        if(!pluginManager->Update()){
            CORE_TRACE("PluginUpdate Failed");
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // 插件清理
    CORE_INFO("Plugin Shut");
    pluginManager->Shut();
    pluginManager->UnLoadPlugin();
}

