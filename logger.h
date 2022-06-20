#pragma once

#include "logger_proxy.h"
#include "writer.h"

#include <fstream>
#include <string>

namespace experis {
    
namespace detail {
    constexpr const char DEFAULT_LOG_FILE_NAME[] = "my_log.log";
    constexpr int MODES = 4;
} // detail


class Logger {
    friend Logger& Log();
public:
    enum Level {ERROR, WARNING, INFO, DEBUG, __NUM_LEVELS__};

    ~Logger() = default;

    LoggerProxy Error();
    LoggerProxy Warning();
    LoggerProxy Info();
    LoggerProxy Debug();
    void SetLevel(enum Level a_level);
    void SetOutput(std::ostream& a_outputStream);

private:
    explicit Logger();
    Logger(const Logger& a_other) = delete;
    Logger& operator=(const Logger& a_other) = delete;

    std::ostream* m_myStream;
    const WriteToLog m_write;
    const DontWrite m_dontWrite;
    const Writer *m_setWriterMode[__NUM_LEVELS__];
};

Logger& Log();

} // experis

