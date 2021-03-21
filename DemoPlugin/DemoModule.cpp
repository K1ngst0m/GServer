//
// Created by npchitman on 3/18/21.
//

#include "DemoModule.h"
#include <iostream>
#include <ctime>

DemoModule::DemoModule(IPluginManager *pluginManager)
: m_pluginManager(pluginManager) {}

bool DemoModule::Init() {
    PLUGIN_INFO("DemoModule Init");
//    return false;
    return true;
}

bool DemoModule::Update() {
    PLUGIN_TRACE("DemoModule Update");
//    return false;
    return true;
}

bool DemoModule::Shut() {
    PLUGIN_INFO("DemoModule Shut");
//    return false;
    return true;
}

void DemoModule::DemoTest() {
    PLUGIN_INFO("DemoModule Test");
}

void DemoModule::OnMsgReceive(const uint64_t nClientID, const uint32_t nMsgID, const char *msg, const uint32_t nLen) {
    PLUGIN_INFO("[DemoModule] Client Received: , \
            ClientID: {} , \
            MsgID: {} , \
            nLen: {} , ",
            nClientID, nMsgID, msg, nLen);
}

void DemoModule::OnClientConnected(uint64_t nClientID) {
    PLUGIN_INFO("[DemoModule] Client Connect");
}

void DemoModule::OnClientLeave(uint64_t nClientID) {
    PLUGIN_INFO("[DemoModule] Client Disconnect");
}

