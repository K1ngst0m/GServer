//
// Created by npchitman on 3/18/21.
//

#include "DynLib.h"


DynLib::DynLib(const char *name) {
    m_strName = name;

    m_strName.append(".so");
}

bool DynLib::Load(){
    std::string strLibPath = "./";
    strLibPath += m_strName;
    // TODO linux 加载动态库
//    dlopen(strLibPath.c_str(), );
}

bool DynLib::Unload() {

    return false;
}

const char *DynLib::GetName() {
    return nullptr;
}

void *DynLib::GetSymbol(const char *szProcName) {
    return nullptr;
}
