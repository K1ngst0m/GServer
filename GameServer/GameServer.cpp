//
// Created by npchitman on 3/18/21.
//

#include "pch.h"
#include "PluginManager.h"
#include <thread>
#include <chrono>

// 入口
int main(int argc, char** argv){
    const char *pluginName = "";

    Log::Init();

    CORE_INFO("Server start");

    // 初始化插件
    CORE_INFO("Plugin Load");
    auto * pluginManager = new PluginManager(pluginName);
    if(!pluginManager->LoadPlugin()){
        return -1;
    }

    CORE_INFO("Plugin Init");
    if(!pluginManager->Init()){
        return -1;
    }

    // 插件运行
    CORE_INFO("Plugin Run");
    while(true){
        CORE_TRACE("plugin update");

        if(!pluginManager->Update()){
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // 插件清理
    pluginManager->Shut();
    pluginManager->UnLoadPlugin();
}

