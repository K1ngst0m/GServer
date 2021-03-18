//
// Created by npchitman on 3/18/21.
//

#ifndef GSERVER_DEMOMODULE_H
#define GSERVER_DEMOMODULE_H

#include <IDemoModule.h>
#include <IPluginManager.h>
#include <INetServer.h>

class DemoModule : public IDemoModule{
public:
    DemoModule(IPluginManager *pluginManager);
    ~DemoModule() = default;

    virtual bool Init() override;
    virtual bool Update() override;
    virtual bool Shut() override;

    virtual void DemoTest() override;

    void OnMsgReceive(const uint64_t nClientID,
                      const uint32_t nMsgID,
                      const char* msg,
                      const uint32_t nLen);

    void OnClientConnected(uint64_t nClientID);
    void OnClientLeave(uint64_t nClientID);

private:
    IPluginManager *m_pluginManager;
    uint64_t m_sayTime;
    INetServer * m_pNetServer;

};


#endif //GSERVER_DEMOMODULE_H
