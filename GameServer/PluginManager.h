//
// Created by npchitman on 3/18/21.
//

#include <IPluginManager.h>
#include "DynLib.h"

#include <set>
#include <unordered_map>
#include <iostream>

class PluginManager : IPluginManager{
public:
    explicit PluginManager(std::string appName);

    bool LoadPlugin() override;
    bool UnLoadPlugin() override;

    bool Init() override;
    bool Update() override;
    bool Shut() override;

    void Registered(IPlugin * plugin) override;
    void UnRegistered(IPlugin * plugin) override;

    void AddModule(const std::string &name, IModule *pModule) override;
    IModule* FindModule(const std::string &name) override;
    void RemoveModule(const std::string &name) override;

    void GetLogger();
private:

    // 原例中typedef定义可读性不高, 改为using
    using DLL_START_PLUGIN_FUNC = void(*)(IPluginManager *);
    using DLL_STOP_PLUGIN_FUNC = void(*)(IPluginManager *);

    std::string m_strAppName;
    std::set<IPlugin*> m_setPlugins;
    std::unordered_map<std::string, IModule*> m_mapModules;
    std::unordered_map<std::string, DynLib*> m_mapPluginLibs;

};
