//
// Created by npchitman on 3/18/21.
//

#include "DynLib.h"
#include <memory>


DynLib::DynLib(const char *name) {
    m_strName = name;
    m_strName.append(".so");
}

bool DynLib::Load(){
    std::string strLibPath = "./";
    strLibPath += m_strName;
    mInst = std::make_unique<void*>(dlopen(strLibPath.c_str(), RTLD_LAZY));
    return mInst != nullptr;
}

bool DynLib::Unload() {
    dlclose(mInst.get());
    return true;
}

const char *DynLib::GetName() {
    return m_strName.c_str();
}

void* DynLib::GetSymbol(const char *szProcName) {
    return dlsym(mInst.get(), szProcName);
}
