//
// Created by npchitman on 3/18/21.
//

#include "DemoPlugin.h"
#include "DemoModule.h"

IPlugin *g_DemoPlugin;

//TODO: linux lib export

DemoPlugin::DemoPlugin(IPluginManager *pluginManager)
: m_pluginManager(pluginManager) {}

void DemoPlugin::Install() {
    m_pluginManager->AddModule<IDemoModule>(new DemoModule(m_pluginManager));
}

void DemoPlugin::Uninstall() {
    m_pluginManager->RemoveModule<IDemoModule>();
}
