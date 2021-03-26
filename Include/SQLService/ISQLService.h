//
// Created by Npchitman on 2021/3/26.
//

#ifndef GSERVER_ISQLSERVICE_H
#define GSERVER_ISQLSERVICE_H

#include "IModule.h"
#include "IQueryResult.h"
#include <functional>

typedef std::function<void(IQueryResult *result, int nRetCode)> SQL_Callback;

struct SQLParam
{
    SQLParam() = default;;
    SQLParam(void *p, uint32_t l)
    {
        data = p;
        length = l;
    }
    void *data;
    uint32_t length;
};

class ISQLService : public IModule
{
public:
    virtual int Open(const char * constr) = 0;
    virtual int ExecuteQuery(IQueryResult **result, const char *cmd) = 0;
    virtual int ExecuteQueryf(IQueryResult **result, const char *cmd, ...) = 0;
    virtual int ExecuteQuery(const char *cmd) = 0;
    virtual int ExecuteQueryf(const char *cmd, ...) = 0;
    virtual int ExecuteBinary(const char *cmd, SQLParam *param) = 0;
    virtual int ExecuteBinaryf(const char *cmd, SQLParam *param, ...) = 0;

    virtual void ExecuteQueryAsync(const char *cmd, SQL_Callback callback = 0, bool bHasResult = true) = 0;
    virtual void ExecuteQueryAsyncf(const char *cmd, SQL_Callback callback = 0, bool bHasResult = true, ...) = 0;
    virtual void ExecuteBinaryAsync(const char *cmd, SQLParam *param, SQL_Callback callback = 0) = 0;
    virtual void ExecuteBinaryAsyncf(const char *cmd, SQLParam *param, SQL_Callback callback = 0, ...) = 0;
};

#endif //GSERVER_ISQLSERVICE_H
