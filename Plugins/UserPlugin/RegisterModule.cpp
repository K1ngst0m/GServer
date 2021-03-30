//
// Created by Npchitman on 2021/3/26.
//

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

}

void RegisterModule::OnClientConnected(uint64_t nClientID) {

}

void RegisterModule::OnClientLeave(uint64_t nClientID) {

}
