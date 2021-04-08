//
// Created by Npchitman on 2021/3/23.
//

#include "pch.h"
#include "LoginModule.h"
#include <NetMsgDefine/Msg.pb.h>

LoginModule::LoginModule(IPluginManager *pluginManager) {
    m_pluginManager = pluginManager;
}

LoginModule::~LoginModule() = default;

bool LoginModule::Init() {
    MODULE_INFO("LoginModule: Init");
    m_pNetServer = m_pluginManager->FindModule<INetServer>();
    m_pSQLService = m_pluginManager->FindModule<ISQLService>();


    MODULE_INFO("LoginModule: Open DataBase");
    m_pSQLService->Open("filename=Resources/Data/data.sqlite");

    m_nMaxUserID = 0;
    IQueryResult *result;
    auto cmd = "SELECT max(USER.userID) FROM User";
    m_pSQLService->ExecuteQuery(&result, cmd);
    if(result && result->Read()){
        m_nMaxUserID = result->get_int32(0);
    }

    MODULE_INFO("LoginModule: Init Server");

    m_pNetServer->Initialization(3001, "47.110.143.150");
    m_pNetServer->AddEventCallBack(this, &LoginModule::OnClientConnected, &LoginModule::OnClientLeave);
    m_pNetServer->AddReceiveCallBack((uint32_t)MsgType::LOGIN_C2S, this, &LoginModule::OnMsgReceive);

    return true;
}

bool LoginModule::Update() {
    MODULE_TRACE("LoginModule: Update");
    return true;
}

bool LoginModule::Shut() {
    MODULE_INFO("LoginModule: Shut");
    return true;
}

void LoginModule::OnMsgReceive(const uint64_t nClientID, const uint32_t nMsgID, const char *msg, const uint32_t nLen) {
    Msg_Login_C2S xMsg;
    xMsg.ParseFromString(msg);
    if (nMsgID == MsgType::LOGIN_C2S) {
        int userId;
        IQueryResult *result;
        m_pSQLService->ExecuteQueryf(&result,
                                     "SELECT userId FROM User WHERE userName='%s' AND passWord='%s'",
                                     xMsg.name().c_str(), xMsg.password().c_str());

        Msg_Login_S2C login;
        login.set_id(-1);
        login.set_result(-1);

        // 1: 成功, 0: 失败, -1: 其他错误
        if(result && result->Read()){
            userId = result->get_int32(0);
            login.set_id(userId);
            login.set_result(1);
            MODULE_INFO("User {} login success.", xMsg.name().c_str());
        }
        else{
            login.set_result(0);
            MODULE_INFO("User {} login failed.", xMsg.name().c_str());
        }

        auto resultData = fmt::format("{}#{}", login.id(), login.result());
        m_pNetServer->SendMsg(nClientID, (void*)resultData.c_str());
    }
}

void LoginModule::OnClientConnected(uint64_t nClientID) {
    MODULE_INFO("Client Connected: {}", nClientID);
}

void LoginModule::OnClientLeave(uint64_t nClientID) {
    MODULE_INFO("Client DisConnected: {}", nClientID);
}
