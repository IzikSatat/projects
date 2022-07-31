#pragma once

#include "writer.h"
#include "logger.h"

namespace myWork {

class SetLevelBase {
public:
    virtual void SetLevel(const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                        , const WriteToLog& a_write
                        , const DontWrite& a_dontWrite) = 0;
    virtual ~SetLevelBase() = default;
};

class SetErrorLevel : public SetLevelBase {
public:
    virtual void SetLevel(const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                        , const WriteToLog& a_write
                        , const DontWrite& a_dontWrite) override;
};

class SetWarningLevel : public SetLevelBase {
public:
    virtual void SetLevel(const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                        , const WriteToLog& a_write
                        , const DontWrite& a_dontWrite) override;
};

class SetInfoLevel : public SetLevelBase {
public:
    virtual void SetLevel(const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                        , const WriteToLog& a_write
                        , const DontWrite& a_dontWrite) override;
};

class SetDebugLevel : public SetLevelBase {
public:
    virtual void SetLevel(const Writer *a_writerMode[Logger::__NUM_LEVELS__]
                        , const WriteToLog& a_write
                        , const DontWrite& a_dontWrite) override;
};

} // namespace myWork
