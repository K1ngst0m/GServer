//
// Created by npchitman on 3/18/21.
//

#ifndef GSERVER_IMODULE_H
#define GSERVER_IMODULE_H
#include "../Common/Log/Log.h"

class IModule{
public:
    virtual bool Init() = 0;
    virtual bool Update() = 0;
    virtual bool Shut() = 0;
};

#endif //GSERVER_IMODULE_H
