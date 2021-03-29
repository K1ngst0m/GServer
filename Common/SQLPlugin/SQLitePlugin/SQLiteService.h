/********************************************************************
	purpose:	数据库服务接口实现类
*********************************************************************/
#pragma once

#include "../Common/SQLService.h"

struct sqlite3;

class SQLiteService :
	public SQLService
{
public:
	explicit SQLiteService(IPluginManager *pluginManager);
	virtual ~SQLiteService();

public:
    int ExecuteQuery(IQueryResult **result, const char *cmd) override;
    int ExecuteQuery(const char *cmd) override;
    int ExecuteBinary(const char *cmd, SQLParam *param) override;

protected:
    int OpenImpl(std::map<std::string, std::string> &strMap) override;

private:
    sqlite3 *_db;
};
