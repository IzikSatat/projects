#include "logger_proxy.h"
#include "writer_buffer.h"
#include "write_by_type.h"

#include <sstream> //stringstream
#include <iomanip> // put_time

namespace myWork {
    
std::mutex LoggerProxy::s_writeMutex{};

inline static std::string BeginLine() {
    const std::chrono::time_point<std::chrono::system_clock> now =
        std::chrono::system_clock::now();

    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream timeAndDate{};
    timeAndDate << std::put_time(std::localtime(&t_c), "%Y-%m-%d %X");
    std::string beginLine{"["};
    beginLine.append(timeAndDate.str());
    beginLine.push_back(']');
    return beginLine;
}

LoggerProxy::LoggerProxy(const OutputStream& a_outputStream, const Writer* a_writeOperation) 
: m_outputStream(a_outputStream)
, m_doWriteOperation(a_writeOperation)
, m_buffer{} {
}

static void PrintFromBuffer(WriterBuffer& a_buffer, const OutputStream& a_outputStream, const Writer* a_writeOperation);

LoggerProxy::~LoggerProxy() {
    if (m_doWriteOperation) {
        s_writeMutex.lock();
        m_doWriteOperation->write(m_outputStream, BeginLine().c_str());
        PrintFromBuffer(m_buffer, m_outputStream, m_doWriteOperation);
        m_doWriteOperation->write(m_outputStream, '\n');
        s_writeMutex.unlock();
    }
}

LoggerProxy& LoggerProxy::operator<<(const char* a_toWrite) {
    bufferDetail::TypeToWrie toWrite;
    toWrite.m_charArray = a_toWrite;
    m_buffer.Push(toWrite, bufferDetail::BufferTypes::P_CHAR);
    return *this;
}

LoggerProxy& LoggerProxy::operator<<(char a_ch) {
    bufferDetail::TypeToWrie toWrite;
    toWrite.m_char = a_ch;
    m_buffer.Push(toWrite, bufferDetail::BufferTypes::CHAR);
    return *this;
}

LoggerProxy& LoggerProxy::operator<<(int a_int) {
    bufferDetail::TypeToWrie toWrite;
    toWrite.m_int = a_int;
    m_buffer.Push(toWrite, bufferDetail::BufferTypes::INT);
    return *this;
}

LoggerProxy& LoggerProxy::operator<<(double a_double) {
    bufferDetail::TypeToWrie toWrite;
    toWrite.m_double = a_double;
    m_buffer.Push(toWrite, bufferDetail::BufferTypes::DOUBLE);
    return *this;
}

static void PrintFromBuffer(WriterBuffer& a_buffer,const OutputStream& a_outputStream, const Writer* a_writeOperation) {
    WritePChar pCharWrite;
    WriteChar charWrite;
    WriteInt intWrite;
    WriteDouble doubleWrite;
    WriteByType *writersArray[bufferDetail::__NUM_OF_BUFFER_TYPES__] = {&pCharWrite
                                                                        ,&charWrite
                                                                        ,&intWrite 
                                                                        ,&doubleWrite};
    for(unsigned int i = a_buffer.NumOfTypes(); 0 < i ; --i ) {
        bufferDetail::BufferPair pair = a_buffer.Pop();
        writersArray[pair.m_type]->WriteToLog(a_outputStream, *a_writeOperation, pair.m_data);
    }
    
}

} // myWork
