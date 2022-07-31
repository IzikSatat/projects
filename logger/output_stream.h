#pragma once

#include <memory>
#include "stream_adapter.h"

namespace myWork {

class OutputStream {
public:
    explicit OutputStream();
    OutputStream(OutputStream& a_other) = delete;
    OutputStream& operator=(OutputStream& a_other) = delete;
    ~OutputStream() = default;

    void SetOutput(std::ostream& a_outputStream);
    void SetOutput(const char *a_ip, int a_port);
    const OutputStream& operator<<(const char *a_toWrite) const;
    const OutputStream& operator<<(char a_toWrite) const;
    const OutputStream& operator<<(int a_toWrite) const;
    const OutputStream& operator<<(double a_toWrite) const;

private:
    AdapterForOstream m_myStream;
    std::unique_ptr<AdapterForServer> m_transmitToServer;
    StreamAdapterBase *m_currentStream;
};

} // namespace myWork