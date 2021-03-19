//
// Created by npchitman on 3/18/21.
//

#include "DynLib.h"
#include <memory>
#include <iostream>


DynLib::DynLib(const char *name) {
    m_strName = "lib";
    m_strName.append(name);
    m_strName.append(".so");
}

bool DynLib::Load(){
    std::string strLibPath = "./";
    strLibPath += m_strName;
    auto handle = dlopen(strLibPath.c_str(), RTLD_LAZY);
    if(!handle){
        std::cerr << "load plugin failed: " << dlerror() << std::endl;
        return false;
    }
    dlerror();
    mInst = std::make_unique<void*>(handle);
    handle_test = handle;
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
    return dlsym(handle_test, szProcName);
//    auto symbol = dlsym(mInst.get(), szProcName);
//    if (dlerror() != nullptr)  {
//        std::cerr << "GetSymbol failure: " << dlerror() << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    return symbol;
}
