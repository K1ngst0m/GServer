//
// Created by Npchitman on 2021/3/23.
//

#ifndef GSERVER_LOGINMODULE_H
#define GSERVER_LOGINMODULE_H

#endif //GSERVER_LOGINMODULE_H

//TODO SQL Service

#include <ILoginModule.h>
#include <IPluginManager.h>
#include <INetServer.h>
#include <SQLService/ISQLService.h>

#include <unordered_map>

class LoginModule: public IModule{
public:
    explicit LoginModule(IPluginManager *pluginManager);
    ~LoginModule();

    bool Init() override;
    bool Update() override;
    bool Shut() override;

    void OnMsgReceive(uint64_t nClientID, uint32_t nMsgID, const char* msg, uint32_t nLen);
    void OnClientConnected(uint64_t nClientID);
    void OnClientLeave(uint64_t nClientID);

private:
    IPluginManager *m_pluginManager;
    INetServer *m_pNetServer;
    ISQLService *m_pSQLService;
    int m_nMaxUserID;
};

