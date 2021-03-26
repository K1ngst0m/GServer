#pragma once
#include "../Common/QueryResult.h"
#include "./sqlite/sqlite3.h"

class SQLiteQueryResult :
    public QueryResult
{
public:
	SQLiteQueryResult(sqlite3_stmt *stmt, uint64_t row_count, uint32_t field_count);
    ~SQLiteQueryResult();

    bool Read() override;
    void SetToBegin() override;
    std::string field_name(int n) override;
    uint32_t length(int32_t n) override;

    uint32_t get_data(int n, char *data) override;
    int32_t get_int32(int n) override;
    int64_t get_int64(int n) override;
    float get_float(int n) override;
    double get_double(int n) override;
    std::string get_string(int n) override;

private:
    sqlite3_stmt *_sqlite_stmt;
};
