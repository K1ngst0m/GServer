//
// Created by npchitman on 3/18/21.
//

#include "pch.h"
#include "PluginManager.h"
#include <Log/Log.h>
#include <thread>
#include <chrono>

// 入口
int main(int argc, char** args){
    Log::Init(0);

    CORE_INFO("Server start");

    // 系统运行参数为插件名
    const char *pluginName = "";
    if (argc > 1){
        pluginName = args[1];
    }

    // 初始化插件
    CORE_INFO("Plugin Load");
    auto * pluginManager = new PluginManager(pluginName);
    if(!pluginManager->LoadPlugin()){
        return -1;
    }

    CORE_INFO("Plugin Init");
    if(!pluginManager->Init()){
        CORE_ERROR("Plugin init failed.");
        return -1;
    }

    CORE_INFO("Plugin Update");
    while(true){
        CORE_TRACE("plugin updating");
        // 插件运行
        if(!pluginManager->Update()){
            CORE_TRACE("{} {}", "test1", "test2");
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // 插件清理
    CORE_INFO("Plugin Shut");
    pluginManager->Shut();
    pluginManager->UnLoadPlugin();
}

