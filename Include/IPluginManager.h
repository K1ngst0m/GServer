//
// Created by npchitman on 3/18/21.
//

#ifndef GSERVER_IPLUGINMANAGER_H
#define GSERVER_IPLUGINMANAGER_H

#include <string>

class IPlugin;
class IModule;

class IPluginManager{
public:

    virtual bool LoadPlugin() = 0;
    virtual bool UnLoadPlugin() = 0;

    virtual bool Init() = 0;
    virtual bool Update() = 0;
    virtual bool Shut() = 0;

    virtual void Registered(IPlugin * plugin) = 0;
    virtual void UnRegistered(IPlugin * plugin) = 0;

    virtual void AddModule(const std::string &name, IModule *pModule) = 0;
    virtual IModule* FindModule(const std::string &name) = 0;
    virtual void RemoveModule(const std::string &name) = 0;

    template<class T>
    void AddModule(IModule* pModule){
        AddModule(typeid(T).name(), pModule);
    }

    template<class T>
    T* FindModule(IModule* pModule){
        return static_cast<T*>(FindModule(typeid(T).name()));
    }

    template<class T>
    void RemoveModule(){
        RemoveModule(typeid(T).name());
    }

};

#endif //GSERVER_IPLUGINMANAGER_H
