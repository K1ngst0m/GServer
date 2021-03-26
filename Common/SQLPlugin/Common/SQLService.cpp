#include "SQLService.h"
#include <cstdarg>

SQLService::SQLService(IPluginManager *pluginManager)
	: m_pPluginManager(pluginManager) {}

SQLService::~SQLService() = default;

bool SQLService::Init()
{
	return true;
}

bool SQLService::Update()
{
	int nResponCount;
	do
	{
		SQL_Respon *pRespon;
		{
			std::lock_guard<std::mutex> lck(m_ResponLock);
			nResponCount = m_listRespon.size();
			if (nResponCount == 0)
				break;
			pRespon = m_listRespon.front();
			m_listRespon.pop_front();
		}
		if (pRespon->_callback)
		{
			pRespon->_callback(pRespon->_result, pRespon->errorCode);
		}
		nResponCount--;
	} while (nResponCount);
	return true;
}

bool SQLService::Shut()
{
	return true;
}

int SQLService::Open(const char * constr)
{
    char *p = strdup(constr);

    char *tmp = p;

    char *param;
    char *val;

    std::map<std::string, std::string> strmap;
	char *buf;
    tmp = strtok_r(tmp, "=", &buf);
    while(tmp)
    {
        param = tmp;
        tmp = strtok_r(nullptr, ";", &buf);
        if(!tmp)
            break;
        val = tmp;
        strmap[param] = val;
        tmp = strtok_r(nullptr, "=", &buf);
    }

    free(p); 
	
	std::thread t1(&SQLService::Run, this);//����һ����֧�̣߳��ص���myThread������
	t1.detach();

    return OpenImpl(strmap);
}

int SQLService::ExecuteQueryf(IQueryResult **result, const char *cmd, ...)
{
    va_list arg_ptr;

    va_start(arg_ptr, cmd);
	vsprintf(_param, cmd, arg_ptr);

    va_end(arg_ptr);
    return ExecuteQuery(result, _param);
}

int SQLService::ExecuteQueryf(const char *cmd, ...)
{
    va_list arg_ptr;

    va_start(arg_ptr, cmd);
	vsprintf(_param, cmd, arg_ptr);

    va_end(arg_ptr);
    return ExecuteQuery(_param);
}


int SQLService::ExecuteBinaryf(const char *cmd, SQLParam *param, ...)
{
    va_list arg_ptr;

    va_start(arg_ptr, cmd);
	vsprintf(_param, cmd, arg_ptr);

    va_end(arg_ptr);
    return ExecuteBinary(_param, param);
}

void SQLService::ExecuteQueryAsync(const char *cmd, SQL_Callback callback, bool bHasResult/* = true*/)
{
	std::lock_guard<std::mutex> lck(m_RequestLock);

	auto *pRequest = new SQL_Request(cmd, callback, NULL, bHasResult);
	m_listRequest.push_back(pRequest);
}

void SQLService::ExecuteQueryAsyncf(const char *cmd, SQL_Callback callback, bool bHasResult/*t = true*/, ...)
{
    va_list arg_ptr;

    va_start(arg_ptr, cmd);
	vsprintf(_param, cmd, arg_ptr);

    va_end(arg_ptr);

    ExecuteQueryAsync(_param, callback, bHasResult);
}

void SQLService::ExecuteBinaryAsync(const char *cmd, SQLParam *param, SQL_Callback callback)
{
	std::lock_guard<std::mutex> lck(m_RequestLock);

	auto *pRequest = new SQL_Request(cmd, callback, param, false);
	m_listRequest.push_back(pRequest);
}

void SQLService::ExecuteBinaryAsyncf(const char *cmd, SQLParam *param, SQL_Callback callback, ...)
{
    va_list arg_ptr;

    va_start(arg_ptr, cmd);
    vsprintf(_param, cmd, arg_ptr);

    va_end(arg_ptr);

    ExecuteBinaryAsync(_param, param, callback);
}

[[noreturn]] void SQLService::Run()
{
	while(true)
	{
		m_RequestLock.lock();
		if(!m_listRequest.empty())
		{
			SQL_Request *pRequest = m_listRequest.front();
			m_listRequest.pop_front();			
			m_RequestLock.unlock();

			SQL_Respon *pRespon;
			if(pRequest->_param)
			{
				int nRet = ExecuteBinary(pRequest->strCmd.c_str(), pRequest->_param);
				pRespon = new SQL_Respon(pRequest->_callback, nullptr, nRet);
			}
			else if(pRequest->_bHasResult)
			{
				IQueryResult *pResult;
				int nRet = ExecuteQuery(&pResult, pRequest->strCmd.c_str());
				pRespon = new SQL_Respon(pRequest->_callback, pResult, nRet);
			}
			else
			{
				int nRet = ExecuteQuery(pRequest->strCmd.c_str());
				pRespon = new SQL_Respon(pRequest->_callback, nullptr, nRet);
			}
			m_ResponLock.lock();
			m_listRespon.push_back(pRespon);
			m_ResponLock.unlock();
		}
		else
		{
			m_RequestLock.unlock();
		}
	}
}