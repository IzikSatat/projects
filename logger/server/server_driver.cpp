#include "server_driver.h"
#include "server_driver_exceptions.h"

#include <sys/socket.h> // struct sockaddr_in
#include <netinet/in.h> // INADDR_ANY htons
#include <fcntl.h> // fcntl
#include <string.h> //memset
#include <unistd.h> // close
#include <iostream>
#include <list>

namespace myWork {

constexpr int FAIL = -1;
constexpr int CLOSE_SOCKET = 0;
constexpr int OK = 1;
constexpr int WAIT_TO_CONECT_QUEUE_SIZE = 128;
constexpr int MAX_CLIENTS = 1000;  
constexpr int BUFFER_SIZE = 1024;  

ServerDriver::ServerDriver(int a_servserPort, bool& a_toRun, const ReciveMessageHandler& a_reciveMessageHandler)
: m_servserPort(a_servserPort)
, m_toRun(a_toRun)
, m_reciveMessageHandler(a_reciveMessageHandler) {
}

int static InitServer(struct sockaddr_in *a_sin, int a_serverPort);
static int CheckNewClient(int a_servSock, size_t a_numOfClients, struct sockaddr_in* a_newClient);
static void clientsRun(std::list<int>& a_clientsSockets,
                        const ReciveMessageHandler& a_reciveMessageHandler,
                        size_t& a_numOfClients, fd_set *a_readfds,
                        fd_set a_temp, int a_activity);
static int NonBlokcing(int _socket);
static int CheckCurClient(int a_currentSocket, const ReciveMessageHandler& a_reciveMessageHandler, int& a_activity, fd_set a_temp);

void ServerDriver::Run() {
    struct sockaddr_in sin = {0};
    int serverSocket = InitServer(&sin, m_servserPort);
    fd_set readfds;
    FD_ZERO(&readfds);
	int maxSd = serverSocket;
	FD_SET(serverSocket, &readfds);
    std::cout << std::endl << "Listening for incoming connections/ data ....." << std::endl;
    size_t numOfClients = 0;
    std::list<int> clientSockets;
    while(m_toRun) {
        fd_set temp = readfds;
        int activity = select(maxSd + 1, &temp, NULL, NULL, NULL);
        if(activity > 0) {
            if(FD_ISSET(serverSocket, &temp)) {
                struct sockaddr_in newClient = {0};
                while(FAIL != CheckNewClient(serverSocket, numOfClients, &newClient))
                {
                    int newSock = ntohs(newClient.sin_port);
                    clientSockets.push_back(newSock);
                    FD_SET(newSock, &readfds);
                    if(newSock > maxSd) {
                        maxSd = newSock;
                    }
                    numOfClients++;
                }
                activity--;
            } 
            clientsRun(clientSockets, m_reciveMessageHandler ,numOfClients, &readfds, temp, activity);
        }
        
    }
}

int static InitServer(struct sockaddr_in *a_sin, int a_serverPort) {
    int optval = 1;
    a_sin->sin_family = AF_INET;
    a_sin->sin_addr.s_addr = INADDR_ANY;
    a_sin->sin_port = htons(a_serverPort);

    int servSock = socket(AF_INET,SOCK_STREAM, 0);
    if(servSock < 0) {
        throw CreateServerSocketFail{};
    }
    if(setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval) ) < 0) {
        throw ReuseSocketFailed{};
    }


    if(bind(servSock, (struct sockaddr *)a_sin, sizeof(sockaddr_in)) < 0) {
        throw BindPortFailed{};
    }

    if(FAIL == NonBlokcing(servSock)) {
        throw NonBlokcingServerSocketFailed{};
    }

    if(listen(servSock, WAIT_TO_CONECT_QUEUE_SIZE) < 0) {
       throw ListenServerFailed{};
    }

    return servSock;
}

static int NonBlokcing(int _socket) {
    int flags = fcntl(_socket, F_GETFL);
    if(FAIL == flags) {
        //perror("error at fcntl.F_GETFL\n");
        return FAIL;
    }
    if(FAIL == fcntl(_socket, F_SETFL, flags | O_NONBLOCK)) {
        //perror("error at fcntl.F_SETFL\n");
        return FAIL;
    }
    return OK;
}

static int CheckNewClient(int a_servSock, size_t a_numOfClients, struct sockaddr_in* a_newClient)
{
    int newSocket = a_servSock;
    socklen_t addrLen = sizeof(struct sockaddr_in);
    memset(a_newClient, 0, addrLen);
    newSocket = accept(a_servSock, (struct sockaddr*)(a_newClient), &addrLen);
    if(newSocket == FAIL) {
        if(errno != EAGAIN && errno != EWOULDBLOCK) { /* real error*/
                perror("accept new client failed");
        }
        return FAIL;
    }

    if(a_numOfClients == MAX_CLIENTS) {
        close(newSocket);
        return FAIL;
    }
    a_newClient->sin_port = htons(newSocket);   
    return OK;
}

static void clientsRun(std::list<int>& a_clientsSockets,
                        const ReciveMessageHandler& a_reciveMessageHandler,
                        size_t& a_numOfClients, fd_set *a_readfds,
                        fd_set a_temp, int a_activity)
{
    std::list<int>::const_iterator current = a_clientsSockets.begin();
    std::list<int>::const_iterator end = a_clientsSockets.end();

    while(current != end && a_activity > 0) {
        int status = CheckCurClient(current.operator*(), a_reciveMessageHandler, a_activity, a_temp);
        std::list<int>::const_iterator next = current;
        next.operator++();
        if(CLOSE_SOCKET == status)
        {
            FD_CLR(current.operator*(), a_readfds);
            close(current.operator*());
           a_clientsSockets.erase(current);
            --a_numOfClients;
        }
        current = next;
    }
}

static int CheckCurClient(int a_currentSocket, const ReciveMessageHandler& a_reciveMessageHandler, int& a_activity, fd_set a_temp) {
    int readByte = BUFFER_SIZE;
    bool dataWasRead = false;
    char buffer[BUFFER_SIZE];

    if(FD_ISSET(a_currentSocket, &a_temp)) {
        while(readByte == BUFFER_SIZE) {
            readByte = recv(a_currentSocket, buffer, BUFFER_SIZE, 0);
            if(readByte == 0 && !dataWasRead) {// if socket closed{
                return CLOSE_SOCKET;
            }
            if(readByte < 0 ) {// fail
                return FAIL;
            }
            else {
                dataWasRead = true;
                a_reciveMessageHandler.operator()(a_currentSocket ,buffer, readByte);
            }
        }
        --a_activity;
    }
    return OK;
}

} // myWork
