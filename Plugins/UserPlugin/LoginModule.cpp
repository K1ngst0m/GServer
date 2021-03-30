//
// Created by Npchitman on 2021/3/23.
//

#include "pch.h"
#include <NetMsgDefine/Msg.pb.h>
#include "LoginModule.h"

LoginModule::LoginModule(IPluginManager *pluginManager) {
    m_pluginManager = pluginManager;
}

LoginModule::~LoginModule() = default;

bool LoginModule::Init() {
    PLUGIN_INFO("LoginModule: Init");
    m_pNetServer = m_pluginManager->FindModule<INetServer>();
    m_pSQLService = m_pluginManager->FindModule<ISQLService>();


    PLUGIN_INFO("LoginModule: Open DataBase");
    m_pSQLService->Open("filename=sqlite3.db");

    m_nMaxUserID = 0;
    IQueryResult *result;
    auto cmd = "SELECT max(USER.userID) FROM User";
    m_pSQLService->ExecuteQuery(&result, cmd);
    if(result && result->Read()){
        m_nMaxUserID = result->get_int32(0);
    }

    PLUGIN_INFO("LoginModule: Init Server");
    m_pNetServer->Initialization(3000, "0.0.0.0");

    m_pNetServer->AddEventCallBack(this, &LoginModule::OnClientConnected, &LoginModule::OnClientLeave);
    m_pNetServer->AddReceiveCallBack((uint32_t)MsgType::LOGIN_C2S, this, &LoginModule::OnMsgReceive);

    return true;
}

bool LoginModule::Update() {
    PLUGIN_TRACE("LoginModule: Update");
    return true;
}

bool LoginModule::Shut() {
    PLUGIN_INFO("LoginModule: Shut");
    return true;
}

void LoginModule::OnMsgReceive(const uint64_t nClientID, const uint32_t nMsgID, const char *msg, const uint32_t nLen) {
    Msg_Login_C2S xMsg;
    xMsg.ParseFromArray(msg + 4, nLen);

    switch (nMsgID) {
        case MsgType::LOGIN_C2S:
        {
            auto *pMsg = (Msg_Login_C2S*)msg;

            int userId = m_nMaxUserID;
            IQueryResult *result;
            m_pSQLService->ExecuteQueryf(&result,
                                         "SELECT userId FROM User WHERE userName='%s'",
                                         pMsg->szname().c_str());
            if(result && result->Read()){
                userId = result->get_int32(0);
            }
            else{
                userId = ++m_nMaxUserID;
                m_pSQLService->ExecuteQueryf(&result,
                                             "INSERT INTO User(userID, userName) VALUES(%d, '%s);",
                                             userId, pMsg->szname().c_str());
            }
            MODULE_INFO("UserLogin: {} : {}", pMsg->szname().c_str(), userId);
            Msg_Login_S2C login;
            login.set_id(userId);
            m_pNetServer->SendMsg(nClientID, &login);
        }
        break;
//        case MsgType::CHAT_C2S:{
//
//        }
//        break;
    }
}

void LoginModule::OnClientConnected(uint64_t nClientID) {
    MODULE_INFO("Client Connected: {}", nClientID);
}

void LoginModule::OnClientLeave(uint64_t nClientID) {
    MODULE_INFO("Client DisConnected: {}", nClientID);
}
