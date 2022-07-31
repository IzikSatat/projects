#pragma once

#include "writer_buffer.h"
#include "writer.h"

namespace myWork {

class WriteByType {
public:
    virtual void WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const = 0;
    virtual ~WriteByType() = default;
};

class WritePChar : public WriteByType {
public:
    virtual void WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const override;
};

class WriteChar : public WriteByType {
public:
    virtual void WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const override;
};

class WriteInt : public WriteByType {
public:
    virtual void WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const override;
};

class WriteDouble : public WriteByType {
public:
    virtual void WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const override;
};

} // namespace myWork
