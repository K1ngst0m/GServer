//
// Created by npchitman on 3/18/21.
//

#include "DemoModule.h"
#include <iostream>
#include <ctime>

DemoModule::DemoModule(IPluginManager *pluginManager)
: m_pluginManager(pluginManager) {}

bool DemoModule::Init() {
    std::cout << "DemoModule Init" << std::endl;
//    return false;
    return true;
}

bool DemoModule::Update() {
    std::cout << "DemoModule Update" << std::endl;
//    return false;
    return true;
}

bool DemoModule::Shut() {
    std::cout << "DemoModule Shut" << std::endl;
//    return false;
    return true;
}

void DemoModule::DemoTest() {
    std::cout << "Demo Test" << std::endl;
}

void DemoModule::OnMsgReceive(const uint64_t nClientID, const uint32_t nMsgID, const char *msg, const uint32_t nLen) {
    std::cout << "Demo OnMsgReceive, Client ID: " << nClientID
    << ", nMsgID: " << nMsgID
    << ", Msg: " << msg
    << ", nLen" << nLen
    << std::endl;
}

void DemoModule::OnClientConnected(uint64_t nClientID) {
    std::cout << "Client Connected: " << nClientID << std::endl;
}

void DemoModule::OnClientLeave(uint64_t nClientID) {
    std::cout << "Client DisConnected" << nClientID << std::endl;
}

