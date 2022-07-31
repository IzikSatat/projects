#pragma once

#include "recive_msg_handler.h"

namespace myWork {

class ServerDriver {
public:
    
    explicit ServerDriver(int a_servserPort, bool& a_toRun, const ReciveMessageHandler& a_reciveMessageHandler);
    ServerDriver(const ServerDriver& a_other) = delete;
    ServerDriver& operator=(const ServerDriver& a_other) = delete;
    ~ServerDriver() = default;
    
    void Run();

private:
    int m_servserPort;
    bool& m_toRun;
    const ReciveMessageHandler& m_reciveMessageHandler;
};

}// myWork