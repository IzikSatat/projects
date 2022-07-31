#include "logger.h"
#include "writer.h"
#include "set_level.h"

#include <mutex>
#include <thread>
#include <atomic>

namespace myWork {

static std::mutex s_initLogMutex;
static const WriteToLog s_write; // class that perform write to log.
static const DontWrite s_dontWrite; // class that not perform write to log.

Logger& Log() {
    static std::atomic<Logger*> theSingleLogger{nullptr};
    Logger *temp = theSingleLogger.load(std::memory_order_relaxed);
    // add barier to be shure that if temp != null it is also constructed. 
    std::atomic_thread_fence(std::memory_order_acquire); // invalidae cache so need to bring from ram
    if (nullptr == temp) {
        std::unique_lock<std::mutex> locker{s_initLogMutex}; // lock so threads not create more than one Logger.
        temp = theSingleLogger.load(std::memory_order_relaxed); // to ensure the thread not create more than one Logger.
        if (nullptr == temp) {
            temp = new Logger{};
            std::atomic_thread_fence(std::memory_order_release); // clean cache all dirty to ram so temp is not null and its member have value
            theSingleLogger.store(temp, std::memory_order_relaxed);
        }
    }
    return *temp;
}

static SetErrorLevel s_setToError;
static SetWarningLevel s_setToWarning;
static SetInfoLevel s_setToInfo;
static SetDebugLevel s_setToDebug;
static SetLevelBase *s_levelsSeter[Logger::__NUM_LEVELS__] = { &s_setToError
                                                    , &s_setToWarning
                                                    , &s_setToInfo
                                                    , &s_setToDebug };
                                                    

Logger::Logger()
: m_myStream()//detail::DEFAULT_LOG_FILE_NAME, std::fstream::app)
, m_setWriterMode{&s_write, &s_write, &s_write, &s_write} {
}

LoggerProxy Logger::Error() {
    return LoggerProxy(m_myStream, m_setWriterMode[Logger::Level::ERROR]);
}

LoggerProxy Logger::Warning() {
    return LoggerProxy(m_myStream, m_setWriterMode[Logger::Level::WARNING]);
}

LoggerProxy Logger::Info() {
    return LoggerProxy(m_myStream, m_setWriterMode[Logger::Level::INFO]);
}

LoggerProxy Logger::Debug() {
    return LoggerProxy(m_myStream, m_setWriterMode[Logger::Level::DEBUG]);
}

void Logger::SetLevel(enum Level a_level) {
    s_levelsSeter[a_level]->SetLevel(m_setWriterMode, s_write, s_dontWrite);
}

void Logger::SetOutput(std::ostream& a_outputStream) {
    m_myStream.SetOutput(a_outputStream); 
}

void Logger::SetOutput(const char *a_ip, int a_port) {
    m_myStream.SetOutput(a_ip, a_port);
}

} // myWork