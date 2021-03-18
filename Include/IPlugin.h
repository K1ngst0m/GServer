//
// Created by npchitman on 3/18/21.
//

#ifndef GSERVER_IPLUGIN_H
#define GSERVER_IPLUGIN_H

#include "IModule.h"
#include <unordered_map>

class IPlugin{
public:
    virtual void Install() = 0;
    virtual void Uninstall() = 0;
};

#endif //GSERVER_IPLUGIN_H
