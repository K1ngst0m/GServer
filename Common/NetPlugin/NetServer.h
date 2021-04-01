#pragma once
#include <INetServer.h>
#include <IPluginManager.h>
#include <unordered_map>
#include <asio.hpp>
#include <asio/basic_socket.hpp>

using asio::ip::tcp;

class User
{
public:
	std::string m_sendData;
	std::string m_recvData;
	uint64_t m_guid;
	void Reset(uint64_t guid)
	{
		m_guid = guid;
		m_sendData.clear();
		m_recvData.clear();
	}
};

class NetServer : public INetServer
{
public:
	explicit NetServer(IPluginManager *pluginManager);
	~NetServer();

	bool Init() override;
	bool Update() override;
	bool Shut() override;

	int Initialization(unsigned short nPort, const char *ip) override;
	bool AddReceiveCallBack(uint32_t nMsgID, const NET_RECEIVE_FUNCTOR_PTR & cb) override;
	bool AddEventCallBack(const NET_EVENT_FUNCTOR_PTR &enter_cb, const NET_EVENT_FUNCTOR_PTR &leave_cb) override;
	void SendMsg(uint64_t nClientID, void* msg) override;
	void SendMsg(uint64_t nClientID, int nMsgID, google::protobuf::Message &msg) override;
private:

    void AddClient(tcp::socket *socket);

    User* GetFreeUser();
	void FreeUser(User* pUser);

	void RemoveClient(tcp::socket *socket);

private:
	IPluginManager *m_pluginManager;

	uint32_t m_nClientGUID{};

	std::unordered_map<uint64_t, User*> m_mapUser;
	std::list<User*> m_listFreeUser;

	std::unordered_map<uint32_t, std::list<NET_RECEIVE_FUNCTOR_PTR>> m_onReceiveCB;
	std::list<NET_EVENT_FUNCTOR_PTR> m_onEnterCB;
	std::list<NET_EVENT_FUNCTOR_PTR> m_onLeaveCB;


    std::shared_ptr<asio::io_context> m_serverContext;
    std::shared_ptr<tcp::socket> m_serverSocket;
    std::shared_ptr<tcp::acceptor> m_serverAcceptor;
    std::unordered_map<std::shared_ptr<tcp::socket>, User*> m_mapClient;
};

