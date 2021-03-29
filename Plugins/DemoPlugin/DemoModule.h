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
    explicit DemoModule(IPluginManager *pluginManager);
    ~DemoModule() = default;

    bool Init() override;
    bool Update() override;
    bool Shut() override;

    void DemoTest() override;

    void OnMsgReceive(uint64_t nClientID,
                      uint32_t nMsgID,
                      const char* msg,
                      uint32_t nLen);

    void OnClientConnected(uint64_t nClientID);
    void OnClientLeave(uint64_t nClientID);

private:
    IPluginManager *m_pluginManager;
    uint64_t m_sayTime{};
    INetServer * m_pNetServer{};

};


#endif //GSERVER_DEMOMODULE_H
