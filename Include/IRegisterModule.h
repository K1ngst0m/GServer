//
// Created by Npchitman on 2021/3/30.
//

#ifndef GSERVER_IREGISTERMODULE_H
#define GSERVER_IREGISTERMODULE_H

#include "IModule.h"

class IRegisterModule : public IModule{
public:
    virtual void Login() = 0;
};

#endif //GSERVER_IREGISTERMODULE_H
