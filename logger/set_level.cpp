#include "set_level.h"

#include "writer.h"
#include "logger.h"

namespace myWork {

void SetErrorLevel::SetLevel(
                            const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                            , const WriteToLog& a_write
                            , const DontWrite& a_dontWrite) {
    a_writerMode[Logger::Level::ERROR] = &a_write;
    a_writerMode[Logger::Level::WARNING] = &a_dontWrite;
    a_writerMode[Logger::Level::INFO] = &a_dontWrite;
    a_writerMode[Logger::Level::DEBUG] = &a_dontWrite;
}

void SetWarningLevel::SetLevel(
                            const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                            , const WriteToLog& a_write
                            , const DontWrite& a_dontWrite) {
    a_writerMode[Logger::Level::ERROR] = &a_write;
    a_writerMode[Logger::Level::WARNING] = &a_write;
    a_writerMode[Logger::Level::INFO] = &a_dontWrite;
    a_writerMode[Logger::Level::DEBUG] = &a_dontWrite;
}

void SetInfoLevel::SetLevel(
                            const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                            , const WriteToLog& a_write
                            , const DontWrite& a_dontWrite) {
    a_writerMode[Logger::Level::ERROR] = &a_write;
    a_writerMode[Logger::Level::WARNING] = &a_write;
    a_writerMode[Logger::Level::INFO] = &a_write;
    a_writerMode[Logger::Level::DEBUG] = &a_dontWrite;
}

void SetDebugLevel::SetLevel(
                            const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                            , const WriteToLog& a_write
                            , const DontWrite& a_dontWrite) {
    a_writerMode[Logger::Level::ERROR] = &a_write;
    a_writerMode[Logger::Level::WARNING] = &a_write;
    a_writerMode[Logger::Level::INFO] = &a_write;
    a_writerMode[Logger::Level::DEBUG] = &a_write;
}

} // namespace myWork
