#pragma once

#include <vector>

namespace myWork {

namespace bufferDetail {

enum BufferTypes { P_CHAR, CHAR, INT, DOUBLE, __NUM_OF_BUFFER_TYPES__};

union TypeToWrie {
    const char* m_charArray;
    char m_char;
    int m_int;
    double m_double;
};

struct BufferPair {
   enum BufferTypes m_type;
   TypeToWrie m_data;
};

static constexpr int MIN_BUFFER_SIZE = 5;

} // bufferDetail

class WriterBuffer {
public:
    explicit WriterBuffer() noexcept;
    WriterBuffer(const WriterBuffer& a_other) = default;
    WriterBuffer& operator=(const WriterBuffer& a_other) = delete;
    ~WriterBuffer() = default;

    void Push(const bufferDetail::TypeToWrie& a_toAdd, enum bufferDetail::BufferTypes a_type);
    const bufferDetail::BufferPair& Pop();
    unsigned int NumOfTypes() const noexcept;

private:
    bufferDetail::BufferPair m_typesToWrite[bufferDetail::MIN_BUFFER_SIZE];
    std::vector<bufferDetail::BufferPair> m_furtherTypesToWrite;
    unsigned int m_arrayCounter; 
    unsigned int m_vectorCounter; 
    unsigned int m_arrayIndex; 
};

} // myWork