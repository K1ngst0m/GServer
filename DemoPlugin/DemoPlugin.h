//
// Created by npchitman on 3/18/21.
//

#ifndef GSERVER_DEMOPLUGIN_H
#define GSERVER_DEMOPLUGIN_H

#include <IPlugin.h>
#include <IPluginManager.h>

class DemoPlugin : public IPlugin{
public:
    explicit DemoPlugin(IPluginManager * pluginManager);
    void Install() override;
    void Uninstall() override;

private:
    IPluginManager * m_pluginManager;
};

#endif //GSERVER_DEMOPLUGIN_H
