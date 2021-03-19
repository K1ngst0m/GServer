//
// Created by npchitman on 3/18/21.
//

#include "pch.h"
#include <thread>
#include "PluginManager.h"
#include <chrono>

// 入口
int main(int argc, char** args){

    // 系统运行参数为插件名
    const char *pluginName = "";
    if (argc > 1){
        pluginName = args[1];
    }

    // 初始化插件
    auto * pluginManager = new PluginManager(pluginName);
    if(!pluginManager->LoadPlugin()){
        return -1;
    }
    if(!pluginManager->Init()){
        return -1;
    }

    while(true){

        // 插件运行
        if(!pluginManager->Update()){
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // 插件清理
    pluginManager->Shut();
    pluginManager->UnLoadPlugin();
}

