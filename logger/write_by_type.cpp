#include "write_by_type.h"
#include "writer_buffer.h"
#include "writer.h"

namespace myWork {

void WritePChar::WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const {
    a_writer.write(a_outputStream, a_toWrite.m_charArray);
}

void WriteChar::WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const {
    a_writer.write(a_outputStream, a_toWrite.m_char);
}

void WriteInt::WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const {
    a_writer.write(a_outputStream, a_toWrite.m_int);
}

void WriteDouble::WriteToLog(const OutputStream& a_outputStream
                            , const Writer& a_writer
                            , bufferDetail::TypeToWrie& a_toWrite) const {
    a_writer.write(a_outputStream, a_toWrite.m_double);
}


} // myWork