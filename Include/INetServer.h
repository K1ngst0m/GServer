//
// Created by npchitman on 3/19/21.
//

#ifndef GSERVER_INETSERVER_H
#define GSERVER_INETSERVER_H

#include "IModule.h"
#include <functional>
#include <memory>
#include <google/protobuf/message.h>

class INetServer:
        public IModule
{
public:
    using NET_RECEIVE_FUNCTOR       = std::function<void(
                                                    const uint64_t nClientID,
                                                    const uint32_t nMsgID,
                                                    const char* msg,
                                                    const uint32_t nLen)>;
    using NET_RECEIVE_FUNCTOR_PTR   = std::shared_ptr<NET_RECEIVE_FUNCTOR>;

    using NET_EVENT_FUNCTOR         = std::function<void(const uint64_t nClientID)>;
    using NET_EVENT_FUNCTOR_PTR     = std::shared_ptr<NET_EVENT_FUNCTOR>;

    virtual int     Initialization(unsigned short nPort, const char * ip) = 0;
    virtual bool    AddReceiveCallBack(uint32_t nMsgID, const NET_RECEIVE_FUNCTOR_PTR &cb) = 0;
    virtual bool    AddEventCallBack(const NET_EVENT_FUNCTOR_PTR &enter_cb, const NET_EVENT_FUNCTOR_PTR &leave_cb) = 0;
    virtual void    SendMsg(uint64_t nClientID, void* msg) = 0;
    virtual void    SendMsg(uint64_t nClientID, int nMsgID, google::protobuf::Message &msg) = 0;

    template<typename BaseType>
    bool AddReceiveCallBack(uint32_t nMsgID, BaseType* pBase,
                            void(BaseType::*handleReceive)(const uint64_t, const uint32_t nMsgID, const char * msg, const uint32_t nLen)){
        NET_RECEIVE_FUNCTOR functor = std::bind(handleReceive, pBase,
                                                std::placeholders::_1,
                                                std::placeholders::_2,
                                                std::placeholders::_3,
                                                std::placeholders::_4);

        NET_RECEIVE_FUNCTOR_PTR functorPtr(new NET_RECEIVE_FUNCTOR(functor));

        return AddReceiveCallBack(nMsgID, functorPtr);
    }

    template<typename BaseType>
    bool AddEventCallBack(BaseType * pBase,
                          void(BaseType::*handleEnter)(uint64_t),
                          void(BaseType::*handleLeave)(uint64_t)){

        NET_EVENT_FUNCTOR functorEnter = std::bind(handleEnter, pBase, std::placeholders::_1);
        NET_EVENT_FUNCTOR_PTR functorEnterPtr(new NET_EVENT_FUNCTOR(functorEnter));

        NET_EVENT_FUNCTOR functorLeave = std::bind(handleLeave, pBase, std::placeholders::_1);
        NET_EVENT_FUNCTOR_PTR functorLeavePtr(new NET_EVENT_FUNCTOR(functorLeave));

        return AddEventCallBack(functorEnterPtr, functorLeavePtr);
    }
};


#endif //GSERVER_INETSERVER_H
