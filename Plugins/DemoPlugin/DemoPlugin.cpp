//
// Created by npchitman on 3/18/21.
//

#include "DemoPlugin.h"
#include "DemoModule.h"

#if defined(__linux__) || defined (__APPLE__)
IPlugin *g_DemoPlugin;

extern "C" void DllStartPlugin(IPluginManager* pm){
    g_DemoPlugin = new DemoPlugin(pm);
    pm->Registered(g_DemoPlugin);
}

extern "C" void DllStopPlugin(IPluginManager* pm){
    pm->UnRegistered(g_DemoPlugin);
}

#endif

#ifdef WIN32
#include <windows.h>
extern "C"
{
    __declspec (dllexport) void DllStartPlugin(IPluginManager * pm){
        g_DemoPlugin = new DemoPlugin(pm);
        pm->Registered(g_DemoPlugin);
    }

    __declspec (dllexport) void DllStopPlugin(IPluginManager* pm){
        pm->UnRegistered(g_DemoPlugin);
    }
}
#endif


DemoPlugin::DemoPlugin(IPluginManager *pluginManager)
: m_pluginManager(pluginManager) {}

void DemoPlugin::Install() {
    m_pluginManager->AddModule<IDemoModule>(new DemoModule(m_pluginManager));
}

void DemoPlugin::Uninstall() {
    m_pluginManager->RemoveModule<IDemoModule>();
}
