#include "logger.h"

#include <fstream>
#include <thread>
#include <iostream>

static constexpr const char* SERVER_ADDRESS = "127.0.0.1";
static constexpr int SERVER_PORT = 1050;

struct T1 {
    void operator()() {
        for (int i = 0 ; i < 1000 ; ++i) {
            myWork::Log().Info() << "This is thread " << 1;
        }
    }
};

struct T2 {
    void operator()() {
        for (int i = 0 ; i < 1000 ; ++i) {
            myWork::Log().Info() << "This is thread " << 2;
        }
    }
};

int main() {
    std::thread t1{ T1{} };
    std::thread t2{ T2{} };

    for (int i = 0 ; i < 100 ; ++i) {
        // ERROR > WARNING > INFO > DEBUG
        myWork::Log().Info() << "This is number " << 2 << ". I love PI (=" << 3.14 << ")";
        myWork::Log().Error() << " this is an error message";
        myWork::Log().Warning() << "this is a warning message";    
        myWork::Log().Info() << "this is an info message";
        myWork::Log().Debug() << "this is a debug message";

        myWork::Log().SetLevel(myWork::Logger::DEBUG);
        myWork::Log().Error() << "This output is seen";
        myWork::Log().Warning() << "This output is seen";    
        myWork::Log().Info() << "This output is seen";
        myWork::Log().Debug() << "This output is seen";

        myWork::Log().SetLevel(myWork::Logger::INFO);
        myWork::Log().Error() << "This output is seen";
        myWork::Log().Warning() << "This output is seen";    
        myWork::Log().Info() << "This output is seen";
        myWork::Log().Debug() << "This output is NOT seen";

        myWork::Log().SetLevel(myWork::Logger::WARNING);
        myWork::Log().Error() << "This output is seen";
        myWork::Log().Warning() << "This output is seen";    
        myWork::Log().Info() << "This output is NOT seen";
        myWork::Log().Debug() << "This output is NOT seen";

        myWork::Log().SetLevel(myWork::Logger::ERROR);
        myWork::Log().Error() << "This output is seen";
        myWork::Log().Warning() << "This output is NOT seen";    
        myWork::Log().Info() << "This output is NOT seen";
        myWork::Log().Debug() << "This output is NOT seen";
    }

    std::fstream logFile1("a.log", std::fstream::app);
    myWork::Log().SetOutput(logFile1);
    myWork::Log().SetLevel(myWork::Logger::INFO);

    for (int i = 0 ; i < 2500 ; ++i) {
        myWork::Log().Error() << "This output will be written to a file" << 1;
        myWork::Log().Error() << "This output will be written to a file" << 1 << std::endl; // This outputs the same as the previous line
        myWork::Log().Warning() << "This output will be written to a file" << 1;    
        myWork::Log().Info() << "This output will be written to a file" << 1;
        myWork::Log().Debug() << "This output is NOT seen or written anywhere";
    }

    myWork::Log().SetOutput(SERVER_ADDRESS, SERVER_PORT);
    for (int i = 0 ; i < 2500 ; ++i) {
        myWork::Log().Error() << "This output will be written to server" << 1;
        myWork::Log().Error() << "This output will be written to server" << 2 << std::endl;
        myWork::Log().Warning() << "This output will be written to server" << 3;    
        myWork::Log().Info() << "This output will be written to server" << 4;
        myWork::Log().Debug() << "This output is NOT seen or written anywhere (server)";
    }

    std::fstream logFile2("b.log", std::fstream::app);
    myWork::Log().SetOutput(logFile2);
    myWork::Log().SetLevel(myWork::Logger::INFO);

    for (int i = 0 ; i < 2500 ; ++i) {
        myWork::Log().Error() << "This output will be written to a file" << 2;
        myWork::Log().Error() << "This output will be written to a file" << 2 << std::endl;
        myWork::Log().Warning() << "This output will be written to a file" << 2;    
        myWork::Log().Info() << "This output will be written to a file" << 2;
        myWork::Log().Debug() << "This output is NOT seen or written anywhere";
    }

    t1.join();
    t2.join();
}