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

//    MODULE_INFO("RegisterModule: Open DataBase");
//    m_pSQLService->Open("filename=Resources/Data/data.sqlite");
//
//    m_nMaxUserID = 0;
//    IQueryResult *result;
//    auto cmd = "SELECT max(USER.userID) FROM User";
//    m_pSQLService->ExecuteQuery(&result, cmd);
//    if(result && result->Read()){
//        m_nMaxUserID = result->get_int32(0);
//    }
//
//    MODULE_INFO("RegisterModule: Init Server");
//
//    m_pNetServer->Initialization(3001, "47.110.143.150");
    m_pNetServer->AddEventCallBack(this, &RegisterModule::OnClientConnected, &RegisterModule::OnClientLeave);
    m_pNetServer->AddReceiveCallBack((uint32_t)MsgType::REGISTER_C2S, this, &RegisterModule::OnMsgReceive);

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
    Msg_Register_C2S xMsg;
    xMsg.ParseFromString(msg);
    if (nMsgID == MsgType::REGISTER_C2S) {
        IQueryResult *result;
        m_pSQLService->ExecuteQueryf(&result,
                                     "SELECT userId FROM User WHERE userName='%s'",
                                     xMsg.name().c_str());

        Msg_Register_S2C regMsg;
        regMsg.set_result(-1);

        // 1: 成功, 0: 失败, -1: 其他错误
        if(result){
            if(result->Read()){
                regMsg.set_result(0);
                MODULE_INFO("User {} register failed, account already exists.", xMsg.name().c_str());
            }
            else{
                regMsg.set_result(1);
                m_pSQLService->ExecuteQueryf(&result,
                                             "INSERT INTO User(userId, userName) VALUES(%d, '%s');",
                                             xMsg.name().c_str(), xMsg.password().c_str());
                if(!result) regMsg.set_result(-1);
                MODULE_INFO("User {} register success.", xMsg.name().c_str());
            }
        }
        else{
            regMsg.set_result(-1);
            MODULE_INFO("User {} register failed, other error", xMsg.name().c_str());
        }

        auto resultData = fmt::format("{}#", regMsg.result());
        m_pNetServer->SendMsg(nClientID, (void*)resultData.c_str());
    }
}

void RegisterModule::OnClientConnected(uint64_t nClientID) {

}

void RegisterModule::OnClientLeave(uint64_t nClientID) {

}
