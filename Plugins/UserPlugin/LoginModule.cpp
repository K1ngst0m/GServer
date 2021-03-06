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
//    std::string tmpMsg (msg);
//    Msg_Login_C2S * xMsg;
//    xMsg->ParseFromString(tmpMsg);
    Msg_Login_C2S xMsg;
    xMsg.ParseFromString(msg);
#if false
    if (nMsgID == MsgType::LOGIN_C2S) {
//        MODULE_TRACE("name: {}, password: {}", xMsg.name(), xMsg.password());
        int userId = m_nMaxUserID;
        IQueryResult *result;
        m_pSQLService->ExecuteQueryf(&result,
                                     "SELECT userId FROM User WHERE userName='%s'",
                                     xMsg.name().c_str());

        if(result && result->Read()){
            userId = result->get_int32(0);
        }
        else{
            userId = ++m_nMaxUserID;
            m_pSQLService->ExecuteQueryf(&result,
                                         "INSERT INTO User(userID, userName) VALUES(%d, '%s);",
                                         userId, xMsg.name().c_str());
        }
        MODULE_INFO("UserLogin: {} : {}", xMsg.name().c_str(), userId);
        Msg_Login_S2C *login;
        login->set_id(userId);
        m_pNetServer->SendMsg(nClientID, login);
    }
#else
    if(xMsg.name() == "admin" && xMsg.password() == "adminadmin") {
        m_pNetServer->SendMsg(nClientID, (void*)"ok###");
    }
#endif
}

void LoginModule::OnClientConnected(uint64_t nClientID) {
    MODULE_INFO("Client Connected: {}", nClientID);
}

void LoginModule::OnClientLeave(uint64_t nClientID) {
    MODULE_INFO("Client DisConnected: {}", nClientID);
}
