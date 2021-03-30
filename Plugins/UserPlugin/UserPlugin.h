//
// Created by Npchitman on 2021/3/23.
//

#ifndef GSERVER_USERPLUGIN_H
#define GSERVER_USERPLUGIN_H

#include <IPlugin.h>
#include <IPluginManager.h>

class UserPlugin : public IPlugin{
public:
    explicit UserPlugin(IPluginManager * pluginManager);

    void Install() override;
    void Uninstall() override;

private:
    IPluginManager *m_pPluginManager;
};

#endif //GSERVER_USERPLUGIN_H
