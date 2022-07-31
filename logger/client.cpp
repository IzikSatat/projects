#include "client.h"
#include "client_exceptions.h"

#include <netinet/in.h> // struct sockaddr_in
#include <unistd.h> // socklen_t
#include <arpa/inet.h>
#include <string.h>

namespace myWork {


static int InitClient(const char* a_ip, int a_serverPort) {
    struct sockaddr_in sin = {0};
    socklen_t addrLen = sizeof(sin);

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(a_ip);;
    sin.sin_port = htons(a_serverPort);

    int clientSock = socket(AF_INET,SOCK_STREAM, 0);    
    if(clientSock < 0) {
        throw SetSocketForClientFailed{};
    }
    
    if(connect(clientSock, (struct sockaddr *)&sin, addrLen) < 0) {
        throw FailedToConnectToServer{};
    }
    return clientSock;
}

Client::Client(const char* a_ip, int a_port)
: m_socket(InitClient(a_ip, a_port)) {
}

Client::~Client() {
    close(m_socket);
}

void Client::Transmit(const char* a_msg) {
    int sendByte = send(m_socket, a_msg, strlen(a_msg) + 1, 0);
    if(sendByte < 0) {
        throw SendToServerFailed{};
    }
}

} // namespace myWork 