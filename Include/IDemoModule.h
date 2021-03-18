//
// Created by npchitman on 3/18/21.
//

#ifndef GSERVER_IDEMOMODULE_H
#define GSERVER_IDEMOMODULE_H

#include "IModule.h"

class IDemoModule : public IModule{
public:
    virtual void DemoTest() = 0;
};

#endif //GSERVER_IDEMOMODULE_H
