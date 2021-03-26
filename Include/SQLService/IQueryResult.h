//
// Created by Npchitman on 2021/3/26.
//

#ifndef GSERVER_IQUERYRESULT_H
#define GSERVER_IQUERYRESULT_H

#include <string>
#include <cstdint>

class IQueryResult
{
public:

    virtual uint64_t row_count() = 0;
    virtual uint32_t field_count() = 0;
    virtual bool Read() = 0;
    virtual void SetToBegin() = 0;
    virtual std::string field_name(int n) = 0;
    virtual uint32_t length(int n) = 0;

    virtual uint32_t get_data(int n, char *p) = 0;
    virtual int32_t get_int32(int n) = 0;
    virtual int64_t get_int64(int n) = 0;
    virtual float get_float(int n) = 0;
    virtual double get_double(int n) = 0;
    virtual std::string get_string(int n) = 0;

};

#endif //GSERVER_IQUERYRESULT_H
