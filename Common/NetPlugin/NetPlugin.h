#pragma once

#include <IPlugin.h>
#include <IPluginManager.h>

class NetPlugin : public IPlugin
{
public:
	explicit NetPlugin(IPluginManager* pluginManager);
	// 通过 IPlugin 继承
	void Install() override;
	void Uninstall() override;

private:
	IPluginManager *m_pPluginManager;
};
