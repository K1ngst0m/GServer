//
// Created by npchitman on 3/18/21.
//

#include "pch.h"
#include "DynLib.h"


DynLib::DynLib(const char *name) {
    m_strName = "lib";
    m_strName.append(name);
    m_strName.append(".so");
}

bool DynLib::Load(){
    std::string strLibPath = "./Libs/";
    strLibPath += m_strName;
    auto handle = dlopen(strLibPath.c_str(), RTLD_LAZY);
    if(!handle){
        std::cerr << "load plugin failed: " << dlerror() << std::endl;
        return false;
    }
    dlerror();
    mInst = handle;
    return mInst != nullptr;
}

bool DynLib::Unload() {
    dlclose(mInst);
    return true;
}

const char *DynLib::GetName() {
    return m_strName.c_str();
}

void* DynLib::GetSymbol(const char *szProcName) {
    return dlsym(mInst, szProcName);
}
