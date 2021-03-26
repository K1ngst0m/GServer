#pragma once

#include <IPlugin.h>
#include <IPluginManager.h>

class SQLitePlugin : public IPlugin
{
public:
	explicit SQLitePlugin(IPluginManager* pluginManager);

	void Install() override;
	void Uninstall() override;

private:
	IPluginManager *m_pPluginManager;
};
