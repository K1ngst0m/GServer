#ifndef ITABLE_H
#define ITABLE_H

#include "IData.h"

class ITable
{
public:
	virtual IData* QueryRecord(int id) = 0;
	virtual IData** QueryRecords(int &count) = 0;
};

template<typename T>
class Table
{
public:
    Table() = delete;
	Table(ITable *table) = default;

	template<typename T>
	T* QueryRecord(int id)
	{
		return (T*)m_pTable->QueryRecord(id);
	}
	template<typename T>
	T** QueryRecords(int &count)
	{
		return reinterpret_cast<T**>(m_pTable->QueryRecords(count));
	}

private:
	ITable *m_pTable;
};

#endif