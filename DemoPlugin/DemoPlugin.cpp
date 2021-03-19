//
// Created by npchitman on 3/18/21.
//

#include "DemoPlugin.h"
#include "DemoModule.h"

IPlugin *g_DemoPlugin;

extern "C" void DllStartPlugin(IPluginManager* pm){
    g_DemoPlugin = new DemoPlugin(pm);
    pm->Registered(g_DemoPlugin);
}

extern "C" void DllStopPlugin(IPluginManager* pm){
    pm->UnRegistered(g_DemoPlugin);
}


DemoPlugin::DemoPlugin(IPluginManager *pluginManager)
: m_pluginManager(pluginManager) {}

void DemoPlugin::Install() {
    m_pluginManager->AddModule<IDemoModule>(new DemoModule(m_pluginManager));
}

void DemoPlugin::Uninstall() {
    m_pluginManager->RemoveModule<IDemoModule>();
}
