#include "pch.h"
#include "NetServer.h"


NetServer::NetServer(IPluginManager *pluginManager)
        : m_pluginManager(pluginManager) {}

NetServer::~NetServer() = default;

bool NetServer::Init() {
    MODULE_INFO("NetService Init");
    m_nClientGUID = 0;
    return true;
}

bool NetServer::Update() {
    MODULE_TRACE("NetService Update");
    if (m_serverAcceptor->is_open()) {
        auto bError = false;

        // 连接客户端
        auto client = std::make_shared<tcp::socket>(tcp::socket(*m_serverContext));
        MODULE_INFO("Wait for connection...");

        try {
            m_serverAcceptor->accept(*client);
        }
        catch (std::exception &e) {
            MODULE_ERROR("NetService Initialization error: {}", e.what());
            m_serverAcceptor->close();
            bError = true;
        }

        if (!bError) {
            MODULE_INFO("Client connected.");
            AddClient(client);
        }

        std::list<std::shared_ptr<tcp::socket>> m_removeClient;

        int len;
        // 处理消息接收
        for (const auto &kv : m_mapClient) {
            std::array<char, 256> buffer{};
            asio::error_code err;

            try{
                MODULE_INFO("Server receive data...");
                len = kv.first->receive(asio::buffer(buffer));

                if (err == asio::error::eof) {
                    MODULE_ERROR("read client data error {}", err);
                    bError = true;
                }

                else {
                    MODULE_INFO("Server receive data: {}", buffer.data());
                    kv.second->m_recvData.append(buffer.data(), len);
                }

            }
            catch (std::exception &e){
                MODULE_ERROR("read client data exception {}", e.what());
                bError = true;
            }

            if (bError) {
                m_removeClient.push_back(kv.first);
            }

            // 处理消息派发
            else if(kv.second->m_recvData.length() >= 4){
                char pData[256];
                for(auto idx = 0; idx < len; idx++){
                    pData[idx] = kv.second->m_recvData[idx];
                }

                size_t nIndex = 0;
                uint16_t nSize = *(uint16_t *) pData;
                uint16_t nType = *(uint16_t *) (pData + sizeof(uint16_t));
//                nType = 1020;
                MODULE_INFO("message ID: {}", nType);

                while ((kv.second->m_recvData.length() - nIndex) >= nSize) {
                    // 处理消息派发
                    auto itr = m_onReceiveCB.find(nType);

                    if (itr != m_onReceiveCB.end()) {

                        for (const auto &onReceive : itr->second) {
                            (*onReceive)
                            (kv.second->m_guid, nType, kv.second->m_recvData.data() + 4, nSize);
                        }
                    }

                    // 处理索引后移
                    nIndex += nSize;
                }

            // 处理发送消息
            if (kv.second->m_sendData.length() > 0) {
                auto nLen = kv.first->send(asio::buffer(kv.second->m_sendData.data(),
                                                        kv.second->m_sendData.length()));

                if (nLen > 0) {
                    kv.second->m_sendData.erase(0, nLen);
                }
                else if (err == asio::error::eof) {
                    MODULE_ERROR("send client data error{}", err);
                    bError = true;
                }
            }
                if (nIndex != 0) {
                    kv.second->m_recvData.erase(0, nIndex);
                }
            }
        }

        // 清理无用客户端
        for (auto &removeClient : m_removeClient) {
            RemoveClient(removeClient);
        }

    }
    return true;
}

bool NetServer::Shut() {
    MODULE_INFO("NetService Shut");
    if (m_serverAcceptor->is_open()) {
        m_serverAcceptor->close();
        m_serverAcceptor.reset();
    }

    m_onEnterCB.clear();
    m_onLeaveCB.clear();

    return true;
}

int NetServer::Initialization(const unsigned short nPort, const char *ip) {
    if (ip == nullptr) { ip = "0.0.0.0"; }
    MODULE_INFO("NetService Initialization: {}:{}", ip, nPort);
    m_serverContext = std::make_shared<asio::io_context>();
    m_serverAcceptor = std::make_shared<tcp::acceptor>(
            tcp::acceptor(*m_serverContext, tcp::endpoint(tcp::v4(), nPort)));

    return 0;
}

bool NetServer::AddReceiveCallBack(const uint32_t nMsgID, const NET_RECEIVE_FUNCTOR_PTR &cb) {
    m_onReceiveCB[nMsgID].push_back(cb);
    return true;
}

bool NetServer::AddEventCallBack(const NET_EVENT_FUNCTOR_PTR &enter_cb, const NET_EVENT_FUNCTOR_PTR &leave_cb) {
    m_onEnterCB.push_back(enter_cb);
    m_onLeaveCB.push_back(leave_cb);
    return true;
}

void NetServer::SendMsg(const uint64_t nClientID, void *msg) {
    auto itr = m_mapUser.find(nClientID);
    if (itr != m_mapUser.end()) {
        std::string pData = (const char *) msg;
        itr->second->m_sendData.clear();
        itr->second->m_sendData.append(pData);
    }
}

void NetServer::SendMsg(const uint64_t nClientID, int nMsgID, google::protobuf::Message &msg) {
    auto itr = m_mapUser.find(nClientID);
    if (itr != m_mapUser.end()) {
        std::string strData;
        msg.SerializeToString(&strData);
        uint16_t nSize = strData.size() + 4;
        uint16_t nType = nMsgID;

        itr->second->m_sendData.append((const char *) &nSize, 2);
        itr->second->m_sendData.append((const char *) &nType, 2);
        itr->second->m_sendData.append(strData.c_str(), strData.size());
    }
}

User *NetServer::GetFreeUser() {
    User *pUser;
    if (m_listFreeUser.empty()) {
        pUser = new User();
    } else {
        pUser = m_listFreeUser.front();
        m_listFreeUser.pop_front();
    }
    pUser->Reset(m_nClientGUID++);
    return pUser;
}

void NetServer::FreeUser(User *pUser) {
    m_mapUser.erase(pUser->m_guid);
    m_listFreeUser.push_back(pUser);
}

void NetServer::AddClient(const std::shared_ptr<tcp::socket> &socket) {
    auto pUser = GetFreeUser();
    m_mapClient.insert(std::make_pair(socket, pUser));
    for (const auto &cb : m_onEnterCB) {
        (*cb)(pUser->m_guid);
        m_mapUser.insert(std::make_pair(pUser->m_guid, pUser));
    }
}

void NetServer::RemoveClient(const std::shared_ptr<tcp::socket> &socket) {
    auto itr = m_mapClient.find(socket);
    if (itr != m_mapClient.end()) {
        auto pUser = itr->second;
        for (const auto &cb : m_onLeaveCB) {
            (*cb)(pUser->m_guid);
        }
        FreeUser(pUser);
        m_mapClient.erase(itr);
    }
}