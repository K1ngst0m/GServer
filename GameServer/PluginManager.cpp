//
// Created by npchitman on 3/19/21.
//
#include "PluginManager.h"
#include "DynLib.h"
#include "IPlugin.h"
#include <nlohmann/json.hpp>
#include <cassert>
#include <utility>
#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;

PluginManager::PluginManager(std::string appName)
: m_strAppName(std::move(appName))
{}

bool PluginManager::LoadPlugin() {
    std::ifstream pluginFS;
    pluginFS.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        pluginFS.open("Plugins.json");
    }
    catch (std::system_error &e){
        std::cout << "read config error: Plugins.json" << std::endl;
        return false;
    }
    json pluginList;
    pluginFS >> pluginList;

#ifdef G_DEBUG
    std::cout << "plugin data: " << pluginData << std::endl;
#endif

    const char * appName = nullptr;
    if(m_strAppName.length() > 0){
        appName = m_strAppName.c_str();
    }

    // TODO: 子插件
    for(const auto & [key, _] : pluginList.items()){
        std::string name = key;
        auto lib = new DynLib(name.c_str());
        if(lib->Load()){
            auto pFunc = (DLL_START_PLUGIN_FUNC)lib
                -> GetSymbol("DllStartPlugin");

            if(!pFunc){
                std::cout << "Load DllStartPlugin Failure: " << name << std::endl;
                return false;
            }
            else{
                std::cout << "Load Plugin :" << name << std::endl;
            }
            pFunc(this);
            m_mapPluginLibs.insert(std::make_pair(name, lib));
        }
        else{
            std::cout << "Load PluginFailure" << name << std::endl;
            return false;
        }
    }
    return true;
}

bool PluginManager::UnLoadPlugin() {

    for(const auto& itr : m_mapPluginLibs){
        auto pLib = itr.second;
        auto pFunc = (DLL_START_PLUGIN_FUNC)pLib->GetSymbol("DllStopPlugin");
        if(pFunc){
            pFunc(this);
        }
        pLib->Unload();

        delete pLib;
    }
    return false;
}

bool PluginManager::Init() {
    for(auto itr : m_mapModules){
        if(!itr.second->Init())
            return false;
    }
    return true;
}

bool PluginManager::Update() {
    for(auto itr : m_mapModules){
        if(!itr.second->Update())
            return false;
    }
    return true;
}

bool PluginManager::Shut() {
    for(auto itr : m_mapModules){
        if(!itr.second->Shut())
            return false;
    }
    return true;
}

void PluginManager::Registered(IPlugin *plugin) {
    m_setPlugins.insert(plugin);
    plugin->Install();
}

void PluginManager::UnRegistered(IPlugin *plugin) {
    m_setPlugins.erase(plugin);
    plugin->Uninstall();
}

void PluginManager::AddModule(const std::string &name, IModule *pModule) {
    if(!FindModule(name)){
        m_mapModules.insert(std::make_pair(name, pModule));
    }
}

IModule *PluginManager::FindModule(const std::string &name) {
    if(auto itr = m_mapModules.find(name);
        itr != m_mapModules.end()
    ){
        return itr->second;
    }
    return nullptr;
}

void PluginManager::RemoveModule(const std::string &name) {
    if(auto itr = m_mapModules.find(name);
            itr != m_mapModules.end()
            ){
        m_mapModules.erase(itr);
    }
}
