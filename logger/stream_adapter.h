#pragma once

#include <ostream>

#include "client.h"

namespace myWork {

class StreamAdapterBase {
public:
    explicit StreamAdapterBase() = default;
    StreamAdapterBase(const StreamAdapterBase& a_other) = delete;
    StreamAdapterBase& operator=(const StreamAdapterBase& a_other) = delete;
    virtual ~StreamAdapterBase() = default;

    virtual StreamAdapterBase& operator<<(const char *a_toWrite) = 0;
    virtual StreamAdapterBase& operator<<(char a_toWrite) = 0;
    virtual StreamAdapterBase& operator<<(int a_toWrite) = 0;
    virtual StreamAdapterBase& operator<<(double a_toWrite) = 0;
};

class AdapterForOstream : public StreamAdapterBase {
public:
    explicit AdapterForOstream(std::ostream& a_stream);
    AdapterForOstream(const AdapterForOstream& a_other) = delete;
    AdapterForOstream& operator=(const AdapterForOstream& a_other) = delete;
    AdapterForOstream& operator=(std::ostream& a_newStream);
    virtual ~AdapterForOstream() override = default;

    virtual StreamAdapterBase& operator<<(const char *a_toWrite) override;
    virtual StreamAdapterBase& operator<<(char a_toWrite) override;
    virtual StreamAdapterBase& operator<<(int a_toWrite) override;
    virtual StreamAdapterBase& operator<<(double a_toWrite) override;

private:
    std::ostream* m_myStream;
};

class AdapterForServer : public StreamAdapterBase {
public:
    explicit AdapterForServer(const char *a_ip, int a_port);
    AdapterForServer(const AdapterForServer& a_other) = delete;
    AdapterForServer& operator=(const AdapterForServer& a_other) = delete;
    virtual ~AdapterForServer() override = default;

    virtual StreamAdapterBase& operator<<(const char *a_toWrite) override;
    virtual StreamAdapterBase& operator<<(char a_toWrite) override;
    virtual StreamAdapterBase& operator<<(int a_toWrite) override;
    virtual StreamAdapterBase& operator<<(double a_toWrite) override;

private:
    Client m_loggerAsClient;
};

} // myWork