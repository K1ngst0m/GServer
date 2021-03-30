//
// Created by Npchitman on 2021/3/26.
//

#ifndef GSERVER_REGISTERMODULE_H
#define GSERVER_REGISTERMODULE_H

#include <IPluginManager.h>
#include <INetServer.h>
#include <SQLService/ISQLService.h>

class RegisterModule: public IModule{
public:
    explicit RegisterModule(IPluginManager *pluginManager);
    ~RegisterModule();

    bool Init() override;
    bool Update() override;
    bool Shut() override;

    void OnMsgReceive(const uint64_t nClientID, const uint32_t nMsgID, const char* msg, const uint32_t nLen);
    void OnClientConnected(uint64_t nClientID);
    void OnClientLeave(uint64_t nClientID);

private:
    IPluginManager *m_pluginManager;
    INetServer *m_pNetServer{};
    ISQLService *m_pSQLService{};
    int m_nMaxUserID{};
};


#endif //GSERVER_REGISTERMODULE_H
