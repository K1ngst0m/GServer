//
// Created by npchitman on 3/18/21.
//

#include "pch.h"
#include "PluginManager.h"
#include "CmdOptions.h"

// 入口
int main(int argc, char** argv){

    const char *pluginName = "";

    // ------------处理运行参数---------------------
    if(argc > 1) {
        auto cmdOpt = BIND_CMD(argc, argv, CmdOption::OptionExists);
        auto getCmd = BIND_CMD(argc, argv, CmdOption::GetOption);

        // -h 显示帮助信息
        cmdOpt("-h", [=](auto isExists){
            if(isExists){
                std::cerr << "usage: Server <options> (-h help | -l loglevel | -p plugin)" << std::endl;
                exit(0);
            }});

        // -l <level> 设置日志等级, 默认为0 (trace)
        getCmd("-l", [&](auto parameter){
            std::string log_level = std::move(parameter);
            if(log_level.c_str())
                Log::Init(log_level.c_str());
            else
                Log::Init();
        });

        // TODO: 从命令行加载插件
        // const char * plugin= getCmdOption(argv, argv + argc, "-p");
    }
    else{
        Log::Init();
    }
    //-------------------------------------------

    // ----------- 服务器启动 -------------------
    CORE_INFO("Server start");

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

