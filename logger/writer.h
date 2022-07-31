#pragma once

#include "output_stream.h"

#include <string>
#include <fstream>

namespace myWork {

class Writer {
public:
    //virtual OutputStream& write(OutputStream& a_stream, const std::string& a_toWrite) const = 0;
    virtual const OutputStream& write(const OutputStream& a_stream, const char *a_toWrite) const = 0;
    virtual const OutputStream& write(const OutputStream& a_stream, char a_toWrite) const = 0;
    virtual const OutputStream& write(const OutputStream& a_stream, int a_toWrite) const = 0;
    virtual const OutputStream& write(const OutputStream& a_stream, double a_toWrite) const = 0;
    virtual operator bool() const = 0;
    virtual ~Writer() = default;
};

class WriteToLog : public Writer {
public:
    //virtual OutputStream& write(OutputStream& a_stream, const std::string& a_toWrite) const override;
    virtual const OutputStream& write(const OutputStream& a_stream, const char *a_toWrite) const override;
    virtual const OutputStream& write(const OutputStream& a_stream, char a_toWrite) const override;
    virtual const OutputStream& write(const OutputStream& a_stream, int a_toWrite) const override;
    virtual const OutputStream& write(const OutputStream& a_stream, double a_toWrite) const override;
    virtual operator bool() const override;
};

class DontWrite : public Writer {
public:
    //virtual OutputStream& write(OutputStream& a_stream, const std::string& a_toWrite) const override;
    virtual const OutputStream& write(const OutputStream& a_stream, const char *a_toWrite) const override;
    virtual const OutputStream& write(const OutputStream& a_stream, char a_toWrite) const override;
    virtual const OutputStream& write(const OutputStream& a_stream, int a_toWrite) const override;
    virtual const OutputStream& write(const OutputStream& a_stream, double a_toWrite) const override;
    virtual operator bool() const override;
};

} // myWork