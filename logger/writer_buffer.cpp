#include "writer_buffer.h"

#include <vector>

namespace myWork {

WriterBuffer::WriterBuffer() noexcept
: m_typesToWrite{}
, m_furtherTypesToWrite()
, m_arrayCounter(0)
, m_vectorCounter(0)
, m_arrayIndex(0) {
}

void WriterBuffer::Push(const bufferDetail::TypeToWrie& a_toAdd, enum bufferDetail::BufferTypes a_type) {
    bufferDetail::BufferPair toAdd = {a_type, a_toAdd};
    if(m_arrayCounter < bufferDetail::MIN_BUFFER_SIZE) {
        m_typesToWrite[m_arrayCounter] = toAdd;
        ++m_arrayCounter;
    }
    else {
        m_furtherTypesToWrite.push_back(toAdd);
        ++m_vectorCounter;
    }
}

const bufferDetail::BufferPair& WriterBuffer::Pop() {
    if( 0 < m_arrayCounter ) {
        const bufferDetail::BufferPair& ret = m_typesToWrite[m_arrayIndex];
        ++m_arrayIndex;
        --m_arrayCounter;
        return ret;
    }
    else {
        const bufferDetail::BufferPair& ret = m_furtherTypesToWrite[m_furtherTypesToWrite.size() - m_vectorCounter];
        --m_vectorCounter;
        return ret;
    }
}

unsigned int WriterBuffer::NumOfTypes() const noexcept {
    return m_arrayCounter + m_vectorCounter;
}

} // myWork