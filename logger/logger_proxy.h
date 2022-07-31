#pragma once

#include "writer.h"
#include "writer_buffer.h"
#include "output_stream.h"

#include <fstream>
#include <string>
#include <mutex>
#include <iostream>

namespace myWork {
    
class LoggerProxy {
public: 
    explicit LoggerProxy(const OutputStream& a_outputStream, const Writer* a_writeOperation);
    LoggerProxy(const LoggerProxy& a_other) = default;
    LoggerProxy& operator=(const LoggerProxy& a_other) = delete;
    ~LoggerProxy();

    //LoggerProxy& operator<<(const std::string& a_toWrite); this function suppress because is not efficiency use string
    LoggerProxy& operator<<(const char* a_toWrite);
    LoggerProxy& operator<<(char a_ch);
    LoggerProxy& operator<<(int a_int);
    LoggerProxy& operator<<(double a_double);
    LoggerProxy& operator<<(std::ostream& (*endl)(std::ostream&)) { return *this; }

private:
    const OutputStream& m_outputStream;
    const Writer* m_doWriteOperation;
    WriterBuffer m_buffer;
    static std::mutex s_writeMutex;
};

} // myWork
