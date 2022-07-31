#include "output_stream.h"

#include <iostream>
#include <cassert>

namespace myWork {

OutputStream::OutputStream()
: m_myStream(std::cout)
, m_transmitToServer(nullptr)
, m_currentStream(&m_myStream) {
    assert(m_currentStream);
}

void OutputStream::SetOutput(std::ostream& a_outputStream) {
    m_myStream = a_outputStream;
    m_currentStream = &m_myStream;
}

void OutputStream::SetOutput(const char *a_ip, int a_port) {
    m_transmitToServer.reset(new AdapterForServer(a_ip, a_port));
    m_currentStream = m_transmitToServer.get();
}

const OutputStream& OutputStream::operator<<(const char *a_toWrite) const {
    m_currentStream->operator<<(a_toWrite);
    return *this;
}

const OutputStream& OutputStream::operator<<(char a_toWrite) const {
    m_currentStream->operator<<(a_toWrite);
    return *this;
}

const OutputStream& OutputStream::operator<<(int a_toWrite) const {
    m_currentStream->operator<<(a_toWrite);
    return *this;
}

const OutputStream& OutputStream::operator<<(double a_toWrite) const {
    m_currentStream->operator<<(a_toWrite);
    return *this;
}

} // namespace myWork