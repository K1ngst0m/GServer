//
// Created by Npchitman on 2021/3/23.
//

#include "UserPlugin.h"
#include "LoginModule.h"
#include "RegisterModule.h"

IPlugin *g_pUserLogin;

extern "C" void DllStartPlugin(IPluginManager* pm)
{
    g_pUserLogin = new UserPlugin(pm);
    pm->Registered(g_pUserLogin);
}

extern "C" void DllStopPlugin(IPluginManager* pm)
{
    pm->UnRegistered(g_pUserLogin);
}

UserPlugin::UserPlugin(IPluginManager *pluginManager) {
    m_pPluginManager = pluginManager;
}

void UserPlugin::Install() {
    m_pPluginManager->AddModule<LoginModule>(new LoginModule(m_pPluginManager));
    m_pPluginManager->AddModule<RegisterModule>(new RegisterModule(m_pPluginManager));
}

void UserPlugin::Uninstall() {
    m_pPluginManager->RemoveModule<LoginModule>();
    m_pPluginManager->RemoveModule<RegisterModule>();
}
