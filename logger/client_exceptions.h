#pragma once

#include <exception>

namespace myWork {

class SetSocketForClientFailed : public std::exception {
    virtual const char *what() { return "Failed to set socket for client"; }
};

class FailedToConnectToServer : public std::exception {
    virtual const char *what() { return "Failed to connect to server"; }
};

class SendToServerFailed : public std::exception {
    virtual const char *what() { return "Failed to send data to server"; }
};

} // myWork