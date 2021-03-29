//
// Created by npchitman on 3/18/21.
//

#ifndef GSERVER_DYNLIB_H
#define GSERVER_DYNLIB_H

#include <string>
#include <dlfcn.h>
#include <memory>

class DynLib{
public:
    explicit DynLib(const char *name);
    ~DynLib() = default;
    bool Load();
    bool Unload();

    const char * GetName();
    void* GetSymbol(const char * szProcName);

protected:

    std::string m_strName;
    void* mInst{};
};

#endif //GSERVER_DYNLIB_H
