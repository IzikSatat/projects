#pragma once

#include <exception>

namespace myWork {

class CanNotEstablishedServer : public std::exception {
    virtual const char *what() { return "Server could not be estaplished"; }
};

class CreateServerSocketFail : public std::exception {
    virtual const char *what() { return "Set socket for server failed"; }
};

class ReuseSocketFailed : public std::exception {
    virtual const char *what() { return "Set server reuse socket failed"; }
};

class BindPortFailed : public std::exception {
    virtual const char *what() { return "Bind server port failed"; }  
};

class NonBlokcingServerSocketFailed : public std::exception {
    virtual const char *what() { return "Set server socket to non blocking failed"; } 
};

class ListenServerFailed : public std::exception {
    virtual const char *what() { return "Set server socket to listening failed"; }
};

} // myWork