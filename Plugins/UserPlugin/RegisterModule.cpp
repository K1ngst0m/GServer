//
// Created by Npchitman on 2021/3/26.
//

#include <NetMsgDefine/Msg.pb.h>
#include "pch.h"
#include "RegisterModule.h"

RegisterModule::RegisterModule(IPluginManager *pluginManager) {
    m_pluginManager = pluginManager;
}

RegisterModule::~RegisterModule() = default;

bool RegisterModule::Init() {
    MODULE_INFO("RegisterModule: Init");
    m_pNetServer = m_pluginManager->FindModule<INetServer>();
    m_pSQLService = m_pluginManager->FindModule<ISQLService>();
    return true;
}

bool RegisterModule::Update() {
    MODULE_TRACE("RegisterModule: Update");
    return true;
}

bool RegisterModule::Shut() {
    MODULE_INFO("RegisterModule: Shut");
    return true;
}

void
RegisterModule::OnMsgReceive(const uint64_t nClientID, const uint32_t nMsgID, const char *msg, const uint32_t nLen) {
    Msg_Login_C2S xMsg;
    xMsg.ParseFromArray(msg + 4, nLen);

    if (nMsgID == MsgType::LOGIN_C2S) {
        auto *pMsg = (Msg_Login_C2S*)msg;

        int userId = m_nMaxUserID;
        IQueryResult *result;
        m_pSQLService->ExecuteQueryf(&result,
                                     "SELECT userId FROM User WHERE userName='%s'",
                                     pMsg->name().c_str());
        if(result && result->Read()){
            userId = result->get_int32(0);
        }
        else{
            userId = ++m_nMaxUserID;
            m_pSQLService->ExecuteQueryf(&result,
                                         "INSERT INTO User(userID, userName) VALUES(%d, '%s);",
                                         userId, pMsg->name().c_str());
        }
        MODULE_INFO("UserLogin: {} : {}", pMsg->name().c_str(), userId);
        Msg_Login_S2C login;
        login.set_id(userId);
        m_pNetServer->SendMsg(nClientID, &login);
    }
}

void RegisterModule::OnClientConnected(uint64_t nClientID) {

}

void RegisterModule::OnClientLeave(uint64_t nClientID) {

}
