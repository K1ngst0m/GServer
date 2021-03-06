#include "../Common/pch.h"
#include "SQLiteQueryResult.h"

SQLiteQueryResult::SQLiteQueryResult(sqlite3_stmt *stmt, uint64_t row_count, uint32_t field_count)
: QueryResult(row_count, field_count)
, _sqlite_stmt(stmt)
{
}

SQLiteQueryResult::~SQLiteQueryResult()
{
    if(_sqlite_stmt)
        sqlite3_finalize(_sqlite_stmt);
}

bool SQLiteQueryResult::Read()
{
	int rc = sqlite3_step(_sqlite_stmt);
    if(rc == SQLITE_ROW)
    {
        return true;
    }
    return false;
}

void SQLiteQueryResult::SetToBegin()
{
	sqlite3_reset(_sqlite_stmt);
}

std::string SQLiteQueryResult::field_name(int n)
{
	return sqlite3_column_name(_sqlite_stmt, n);
}

uint32_t SQLiteQueryResult::length(int n)
{
	return sqlite3_column_bytes(_sqlite_stmt, n);
}


uint32_t SQLiteQueryResult::get_data(int n, char *data)
{
	uint32_t l = length(n);
	memcpy(data, sqlite3_column_blob(_sqlite_stmt, n), l);
    return l;
}

int32_t SQLiteQueryResult::get_int32(int n)
{
	return sqlite3_column_int(_sqlite_stmt, n);
}

int64_t SQLiteQueryResult::get_int64(int n)
{
	return sqlite3_column_int64(_sqlite_stmt, n);
}

float SQLiteQueryResult::get_float(int n)
{
	return (float)sqlite3_column_double(_sqlite_stmt, n);
}

double SQLiteQueryResult::get_double(int n)
{
	return sqlite3_column_double(_sqlite_stmt, n);
}

std::string SQLiteQueryResult::get_string(int n)
{
	const char *p = (const char*)sqlite3_column_text(_sqlite_stmt, n);
    return p ? p : "";
}
