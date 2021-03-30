#pragma once
#include <INetServer.h>
#include <IPluginManager.h>
#include <unordered_map>

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

class NetServer :
	public INetServer
{
public:
	explicit NetServer(IPluginManager *pluginManager);
	~NetServer();

	// ͨ�� IModule �̳�
	bool Init() override;
	bool Update() override;
	bool Shut() override;

	// ͨ�� INetServer �̳�
	int Initialization(unsigned short nPort, const char *ip) override;
	bool AddReceiveCallBack(uint32_t nMsgID, const NET_RECEIVE_FUNCTOR_PTR & cb) override;
	bool AddEventCallBack(const NET_EVENT_FUNCTOR_PTR &enter_cb, const NET_EVENT_FUNCTOR_PTR &leave_cb) override;
	void SendMsg(uint64_t nClientID, void* msg) override;
	void SendMsg(uint64_t nClientID, int nMsgID, google::protobuf::Message &msg) override;

private:
	User* GetFreeUser();
	void FreeUser(User* pUser);

	void AddClient(int socket);
	void RemoveClient(int socket);

private:
	IPluginManager *m_pluginManager;
	int m_serverSocket{};

	uint32_t m_nClientGUID{};

	std::unordered_map<uint64_t, User*> m_mapClient;
	std::unordered_map<uint64_t, User*> m_mapUser;
	std::list<User*> m_listFreeUser;

	std::unordered_map<uint32_t, std::list<NET_RECEIVE_FUNCTOR_PTR>> m_onReceiveCB;
	std::list<NET_EVENT_FUNCTOR_PTR> m_onEnterCB;
	std::list<NET_EVENT_FUNCTOR_PTR> m_onLeaveCB;
};

