#include "pch.h"
#include "NetServer.h"

NetServer::NetServer(IPluginManager *pluginManager)
	: m_pluginManager(pluginManager)
{
}


NetServer::~NetServer()
= default;

bool NetServer::Init()
{

	m_serverSocket = -1;

	m_nClientGUID = 0;

	return true;
}

bool NetServer::Update()
{
	if (m_serverSocket != -1)
	{
		int  client;
		int nsize = sizeof(sockaddr);
		sockaddr    clientAddr{};

		client = accept(m_serverSocket, &clientAddr, reinterpret_cast<socklen_t *>(&nsize));//????????????
		if (client != -1)
		{
			AddClient(client);
		}

		std::list<uint64_t> m_removeClient;
		for (auto kv : m_mapClient)
		{
			char szBuf[255];
			int nLen = recv(kv.first, szBuf, 1024, 0);
			bool bError = false;
			if (nLen > 0)
			{
				kv.second->m_recvData.append(szBuf, nLen);
			}
			else
			{
			    // TODO : error
//				if (GetLastError() != WSAEWOULDBLOCK)
//				{
//					bError = true;
//				}
			}

			if (!bError)
			{
				if (kv.second->m_sendData.length() > 0)
				{
					int nLen = send((int)kv.first, kv.second->m_sendData.data(), kv.second->m_sendData.length(), 0);
					if (nLen > 0)
					{
						kv.second->m_sendData.erase(0, nLen);
					}
					else
					{
					    // TODO : error
//						if (GetLastError() != WSAEWOULDBLOCK)
//						{
//							bError = true;
//						}
					}
				}
			}
			if(bError)
			{
				m_removeClient.push_back(kv.first);
			}
			else
			{
				if (kv.second->m_recvData.length() >= 4)
				{
					const char *pData = kv.second->m_recvData.data();
					size_t nIndex = 0;
					uint16_t nSize = *(uint16_t*)pData;
					uint16_t nType = *(uint16_t*)(pData+sizeof(uint16_t));

					while ((kv.second->m_recvData.length()-nIndex) >= nSize)
					{
						auto itr = m_onReceiveCB.find(nType);
						if (itr != m_onReceiveCB.end())
						{
							for (const auto& onReceive : itr->second)
							{
								(*onReceive)(kv.second->m_guid, nType, kv.second->m_recvData.data() + nIndex, nSize);
							}
						}
						nIndex += nSize;
					}
					if (nIndex != 0)
					{
						kv.second->m_recvData.erase(0, nIndex);
					}
				}
			}
		}
		for (auto removeClient : m_removeClient)
		{
			RemoveClient(removeClient);
		}
	}
	return true;
}

bool NetServer::Shut()
{
	if (m_serverSocket != -1)
	{
	    close(m_serverSocket);
		m_serverSocket = -1;
	}

	m_onEnterCB.clear();
	m_onLeaveCB.clear();

	return true;
}

int NetServer::Initialization(const unsigned short nPort, const char *ip /*= nullptr*/)
{
	m_serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ip == nullptr)
	{
		ip = "127.0.0.1";
	}
	sockaddr_in sockAddr{};
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(ip);
    sockAddr.sin_port = htons(nPort);

	bind(m_serverSocket, (const struct sockaddr *)&sockAddr, sizeof(sockAddr));

	listen(m_serverSocket, 1);

	int mode = 1;
	ioctl(m_serverSocket, FIONBIO, (u_long *)&mode);

	return 0;
}

bool NetServer::AddReceiveCallBack(const uint32_t nMsgID, const NET_RECEIVE_FUNCTOR_PTR & cb)
{
	m_onReceiveCB[nMsgID].push_back(cb);
	return true;
}

bool NetServer::AddEventCallBack(const NET_EVENT_FUNCTOR_PTR &enter_cb, const NET_EVENT_FUNCTOR_PTR &leave_cb)
{
	m_onEnterCB.push_back(enter_cb);
	m_onLeaveCB.push_back(leave_cb);
	return true;
}

void NetServer::SendMsg(const uint64_t nClientID, void* msg)
{
	auto itr = m_mapUser.find(nClientID);
	if (itr != m_mapUser.end())
	{
		const char *pData = (const char*)msg;
		itr->second->m_sendData.append(pData, *(uint16_t*)(pData));
	}
}
void NetServer::SendMsg(const uint64_t nClientID, int nMsgID, google::protobuf::Message &msg)
{
	auto itr = m_mapUser.find(nClientID);
	if (itr != m_mapUser.end())
	{
		std::string strData;
		msg.SerializeToString(&strData);
		uint16_t nSize = strData.size() + 4;
		uint16_t nType = nMsgID;

		itr->second->m_sendData.append((const char*)&nSize, 2);
		itr->second->m_sendData.append((const char*)&nType, 2);
		itr->second->m_sendData.append(strData.c_str(), strData.size());
	}
}

User* NetServer::GetFreeUser()
{
	User *pUser;
	if (m_listFreeUser.empty())
	{
		pUser = new User();
	}
	else
	{
		pUser = m_listFreeUser.front();
		m_listFreeUser.pop_front();
	}
	pUser->Reset(m_nClientGUID++);
	return pUser;
}

void NetServer::FreeUser(User* pUser)
{
	m_mapUser.erase(pUser->m_guid);
	m_listFreeUser.push_back(pUser);
}

void NetServer::AddClient(int socket)
{
	auto pUser = GetFreeUser();
	m_mapClient.insert(std::make_pair(socket, pUser));
	for (const auto& cb : m_onEnterCB)
	{
		(*cb)(pUser->m_guid);
		m_mapUser.insert(std::make_pair(pUser->m_guid, pUser));
	}
}

void NetServer::RemoveClient(int socket)
{
	auto itr = m_mapClient.find(socket);
	if (itr != m_mapClient.end())
	{
		auto pUser = itr->second;
		for (const auto& cb : m_onLeaveCB)
		{
			(*cb)(pUser->m_guid);
		}
		FreeUser(pUser);
		m_mapClient.erase(itr);
	}
}