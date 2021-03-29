//
// Created by npchitman on 3/18/21.
//

#include "pch.h"
#include "DemoModule.h"

DemoModule::DemoModule(IPluginManager *pluginManager)
: m_pluginManager(pluginManager) {}

bool DemoModule::Init() {
    MODULE_INFO("DemoModule Init");
//    return false;
    return true;
}

bool DemoModule::Update() {
    MODULE_TRACE("DemoModule Update");
//    return false;
    return true;
}

bool DemoModule::Shut() {
    MODULE_INFO("DemoModule Shut");
//    return false;
    return true;
}

void DemoModule::DemoTest() {
    MODULE_INFO("DemoModule Test");
}

void DemoModule::OnMsgReceive(const uint64_t nClientID, const uint32_t nMsgID, const char *msg, const uint32_t nLen) {
    MODULE_INFO("[DemoModule] Client Received: , \
            ClientID: {} , \
            MsgID: {} , \
            nLen: {} , ",
            nClientID, nMsgID, msg, nLen);
}

void DemoModule::OnClientConnected(uint64_t nClientID) {
    MODULE_INFO("[DemoModule] Client Connect");
}

void DemoModule::OnClientLeave(uint64_t nClientID) {
    MODULE_INFO("[DemoModule] Client Disconnect");
}

