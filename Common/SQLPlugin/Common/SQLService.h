#pragma once

#include <SQLService/ISQLService.h>
#include <IPluginManager.h>


class SQL_Request
{
public:
	SQL_Request(const char *cmd, SQL_Callback callback, SQLParam *param, bool bHasResult)
	{
		strCmd = cmd;
		_callback = std::move(callback);
		_param = param;
		_bHasResult = bHasResult;
	}
	std::string strCmd;
	SQL_Callback _callback;
	SQLParam *_param;
	bool _bHasResult ;
};

class SQL_Response
{
public:
	SQL_Response(SQL_Callback callback, IQueryResult *result, bool retCode)
	{
		_result = result;
		_callback = std::move(callback);
		errorCode = retCode;
	}
	SQL_Callback _callback;
	IQueryResult *_result;
	int errorCode;
};

class SQLService : public ISQLService
{
public:
	explicit SQLService(IPluginManager *pluginManager);
	~SQLService();

	// Í¨¹ý ISQLService ¼Ì³Ð
	bool Init() override;
	bool Update() override;
	bool Shut() override;

    int Open(const char * constr) override;

    int ExecuteQuery(IQueryResult **result, const char *cmd) override = 0;
    int ExecuteQueryf(IQueryResult **result, const char *cmd, ...) override;
    int ExecuteQuery(const char *cmd) override = 0;
    int ExecuteQueryf(const char *cmd, ...) override;
    
    int ExecuteBinary(const char *cmd, SQLParam *param) override = 0;
    int ExecuteBinaryf(const char *cmd, SQLParam *param, ...) override;
		
    void ExecuteQueryAsync(const char *cmd, SQL_Callback callback, bool bHasResult) override;
    void ExecuteQueryAsyncf(const char *cmd, SQL_Callback callback, bool bHasResult, ...) override;
    void ExecuteBinaryAsync(const char *cmd, SQLParam *param, SQL_Callback callback) override;
    void ExecuteBinaryAsyncf(const char *cmd, SQLParam *param, SQL_Callback callback, ...) override;

    [[noreturn]] void Run();

protected:
	SQLService() = default;
    virtual int OpenImpl(std::map<std::string, std::string> &strMap) = 0;
    char _param[1024]{};

private:
	std::mutex m_RequestLock;
	std::list<SQL_Request*> m_listRequest;

	std::mutex mResponseLock;
	std::list<SQL_Response*> m_listResponse;
	IPluginManager *m_pPluginManager;
};
