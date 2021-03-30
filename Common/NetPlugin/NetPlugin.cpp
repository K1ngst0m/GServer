// NetPlugin.cpp : 定义 DLL 应用程序的导出函数。
//

#include "pch.h"
#include "NetPlugin.h"
#include "NetServer.h"

IPlugin *g_NetPlugin;

extern "C" void DllStartPlugin(IPluginManager* pm)
{
	g_NetPlugin = new NetPlugin(pm);
	pm->Registered(g_NetPlugin);
}

extern "C" void DllStopPlugin(IPluginManager* pm)
{
	pm->UnRegistered(g_NetPlugin);
}

NetPlugin::NetPlugin(IPluginManager* pluginManager)
	: m_pPluginManager(pluginManager)
{
}

void NetPlugin::Install()
{
	m_pPluginManager->AddModule<INetServer>(new NetServer(m_pPluginManager));
}

void NetPlugin::Uninstall()
{
	m_pPluginManager->RemoveModule<INetServer>();
}
