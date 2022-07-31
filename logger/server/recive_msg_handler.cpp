#include "recive_msg_handler.h"

#include <string.h>
#include <sys/socket.h>
#include <iostream>

namespace myWork {

ReciveMessageHandler::ReciveMessageHandler() {
}

void ReciveMessageHandler::operator()(int a_reciveFromSock, void* a_recivedMsg, size_t a_msgSize) const{
    char* msg = reinterpret_cast<char*>(a_recivedMsg);
    msg[a_msgSize] = '\0';
    std::cout << "Logger: " << msg << std::endl;
}

}// myWork
