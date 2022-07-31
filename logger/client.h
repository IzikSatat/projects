#pragma once

namespace myWork {

class Client {
public:
    Client(const char* a_ip, int a_port);
    Client(const Client& a_other) = delete;
    Client& operator=(const Client& a_other) = delete;
    ~Client();

    void Transmit(const char* a_msg);

private:
    int m_socket;
};

} // myWork