/********************************************************************
	purpose:	???????????????
*********************************************************************/
#include "../Common/pch.h"
#include "SQLiteService.h"
#include "SQLiteQueryResult.h"

//-----------------------------------------------------
// 初始化
//-----------------------------------------------------
SQLiteService::SQLiteService(IPluginManager *pluginManager)
        : SQLService(pluginManager) {
    _db = nullptr;
}

//-----------------------------------------------------
// 关闭数据库
//-----------------------------------------------------
SQLiteService::~SQLiteService() {
    if (_db != nullptr)
        sqlite3_close(_db);
}

//-----------------------------------------------------
// 打开数据库
//-----------------------------------------------------
int SQLiteService::OpenImpl(std::map<std::string, std::string> &strMap) {
    return sqlite3_open(strMap["filename"].c_str(), &_db);
}

//-----------------------------------------------------
//
//-----------------------------------------------------
int SQLiteService::ExecuteQuery(IQueryResult **result, const char *cmd) {
    *result = nullptr;

    sqlite3_stmt *stmt;
    int ret = sqlite3_prepare(_db, cmd, strlen(cmd), &stmt, nullptr);

    if (ret != SQLITE_OK)
        return ret;

    *result = new SQLiteQueryResult(stmt, sqlite3_data_count(stmt), sqlite3_column_count(stmt));

    return ret;
}

int SQLiteService::ExecuteQuery(const char *cmd) {
    char *errMsg;

    int ret = sqlite3_exec(_db, cmd, nullptr, nullptr, &errMsg);

    if (ret != SQLITE_OK)
        free(errMsg);

    return ret;
}

int SQLiteService::ExecuteBinary(const char *cmd, SQLParam *param) {
    sqlite3_stmt *stmt;
    int ret;

    do {
        ret = sqlite3_prepare(_db, cmd, -1, &stmt, nullptr);
        if (ret != SQLITE_OK) {
            break;
        }

        uint32_t count = sqlite3_bind_parameter_count(stmt);

        for (auto i = 0; i < count; i++) {
            ret = sqlite3_bind_blob(stmt, i + 1, param[i].data, param[i].length, SQLITE_STATIC);
            if (ret != SQLITE_OK) {
                break;
            }
        }
        ret = sqlite3_step(stmt);

    } while (false);

    return ret;
}