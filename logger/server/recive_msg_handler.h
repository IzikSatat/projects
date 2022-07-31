#pragma once

#include <stdlib.h> // size_t

namespace myWork {

class ReciveMessageHandler {
public:
    explicit ReciveMessageHandler();
    ReciveMessageHandler(const ReciveMessageHandler& a_other) = delete;
    ReciveMessageHandler& operator=(const ReciveMessageHandler& a_other) = delete;
    ~ReciveMessageHandler() = default;
    
    void operator()(int a_reciveFromSock, void* a_recivedMsg, size_t a_msgSize) const;
};

}// myWork
