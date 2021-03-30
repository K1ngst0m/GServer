//
// Created by Npchitman on 2021/3/30.
//

#ifndef GSERVER_ILOGINMODULE_H
#define GSERVER_ILOGINMODULE_H

#include "IModule.h"

class ILoginModule : public IModule{
public:
    virtual void Login() = 0;
};

#endif //GSERVER_ILOGINMODULE_H
