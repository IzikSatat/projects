#include "writer.h"

namespace myWork
{

    const OutputStream &WriteToLog::write(const OutputStream &a_stream, const char *a_toWrite) const
    {
        a_stream  << a_toWrite;
        return a_stream;
    }

    const OutputStream &WriteToLog::write(const OutputStream &a_stream, char a_toWrite) const
    {
        a_stream << a_toWrite;
        return a_stream;
    }

    const OutputStream &WriteToLog::write(const OutputStream &a_stream, int a_toWrite) const
    {
        a_stream << a_toWrite;
        return a_stream;
    }

    const OutputStream &WriteToLog::write(const OutputStream &a_stream, double a_toWrite) const
    {
        a_stream << a_toWrite;
        return a_stream;
    }

    WriteToLog::operator bool() const
    {
        return true;
    }

    const OutputStream &DontWrite::write(const OutputStream &a_stream, const char *a_toWrite) const
    {
        // do nothing
        return a_stream;
    }

    const OutputStream &DontWrite::write(const OutputStream &a_stream, char a_toWrite) const
    {
        // do nothing
        return a_stream;
    }

    const OutputStream &DontWrite::write(const OutputStream &a_stream, int a_toWrite) const
    {
        // do nothing
        return a_stream;
    }

    const OutputStream &DontWrite::write(const OutputStream &a_stream, double a_toWrite) const
    {
        // do nothing
        return a_stream;
    }

    DontWrite::operator bool() const
    {
        return false;
    }

} // myWork
