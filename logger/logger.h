#pragma once

#include "logger_proxy.h"
#include "writer.h"

#include <fstream>
#include <string>

namespace myWork {

class Logger {
    friend Logger& Log(); // logger is singleton
public:
    enum Level {ERROR, WARNING, INFO, DEBUG, __NUM_LEVELS__};

    ~Logger() = default;

    LoggerProxy Error();
    LoggerProxy Warning();
    LoggerProxy Info();
    LoggerProxy Debug();
    void SetLevel(enum Level a_level);
    void SetOutput(std::ostream& a_outputStream);
    void SetOutput(const char *a_ip, int a_port);

private:
    explicit Logger();
    Logger(const Logger& a_other) = delete;
    Logger& operator=(const Logger& a_other) = delete;

    OutputStream m_myStream;
    const Writer *m_setWriterMode[__NUM_LEVELS__];
};

Logger& Log();

} // myWork

