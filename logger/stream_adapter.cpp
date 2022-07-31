#include "stream_adapter.h"

#include <cassert> //assert
#include <stdio.h> // sprintf

#define NUM_OF_DIGIT 16

namespace myWork { 

AdapterForOstream::AdapterForOstream(std::ostream& a_stream)
: m_myStream(& a_stream) {
    assert(m_myStream);
}

AdapterForOstream& AdapterForOstream::operator=(std::ostream& a_newStream) {
    m_myStream = &a_newStream;
    return *this;
}

StreamAdapterBase& AdapterForOstream::operator<<(const char *a_toWrite) {
    std::ostream& myStream = *m_myStream;
    myStream << (a_toWrite);
    return *this;
}

StreamAdapterBase& AdapterForOstream::operator<<(char a_toWrite) {
    std::ostream& myStream = *m_myStream;
    myStream << (a_toWrite);
    return *this;
}

StreamAdapterBase& AdapterForOstream::operator<<(int a_toWrite) {
    std::ostream& myStream = *m_myStream;
    myStream << (a_toWrite);
    return *this;
}

StreamAdapterBase& AdapterForOstream::operator<<(double a_toWrite) {
    std::ostream& myStream = *m_myStream;
    myStream << (a_toWrite);
    return *this;
}

AdapterForServer::AdapterForServer(const char *a_ip, int a_port)
: m_loggerAsClient(a_ip, a_port) {
}

StreamAdapterBase& AdapterForServer::operator<<(const char *a_toWrite) {
    m_loggerAsClient.Transmit(a_toWrite);
    return *this;
}

StreamAdapterBase& AdapterForServer::operator<<(char a_toWrite) {
    m_loggerAsClient.Transmit(&a_toWrite);
    return *this;
}

StreamAdapterBase& AdapterForServer::operator<<(int a_toWrite) {
    char toTransmit[NUM_OF_DIGIT];
    sprintf(toTransmit, "%d", a_toWrite);
    m_loggerAsClient.Transmit(toTransmit);
    return *this;
}

StreamAdapterBase& AdapterForServer::operator<<(double a_toWrite) {
    char toTransmit[NUM_OF_DIGIT];
    sprintf(toTransmit, "%f", a_toWrite);
    m_loggerAsClient.Transmit(toTransmit);
    return *this;
}

} // myWork