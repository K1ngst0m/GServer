// NetPlugin.cpp : 定义 DLL 应用程序的导出函数。
//

#include "pch.h"
#include "NetPlugin.h"
#include "NetServer.h"

IPlugin *g_NetPlugin;

extern "C" void DllStartPlugin(IPluginManager* pm)
{
    PLUGIN_INFO("NetPlugin: DllStartPlugin");
	g_NetPlugin = new NetPlugin(pm);
	pm->Registered(g_NetPlugin);
}

extern "C" void DllStopPlugin(IPluginManager* pm)
{
    PLUGIN_INFO("NetPlugin: DllStopPlugin");
	pm->UnRegistered(g_NetPlugin);
}

NetPlugin::NetPlugin(IPluginManager* pluginManager)
	: m_pPluginManager(pluginManager)
{
    PLUGIN_INFO("NetPlugin: Constructor");
}

void NetPlugin::Install()
{
    PLUGIN_INFO("NetPlugin: Install");
	m_pPluginManager->AddModule<INetServer>(new NetServer(m_pPluginManager));
}

void NetPlugin::Uninstall()
{
    PLUGIN_INFO("NetPlugin: Uninstall");
	m_pPluginManager->RemoveModule<INetServer>();
}
