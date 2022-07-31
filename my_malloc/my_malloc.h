#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__


/*
NAME: MyMallocInit.
DESCRIPTION: This function prepare bloke size memory
             to be dynamic allocation storage.
INPUT: _memory - block size of free memory (already allocated by os).
        _memorySize the size(in byte) of the given blokc.
OUTPUT:non. only set the _memory.
NOTE: if _memorySize < 32 (bytes) or is not in multiple of 8 the memory will
        be not initialized.
    After initializiation only _memorySize-24 bytes are available
    for client usage.
 */
void MyMallocInit(void* _memory, size_t _memorySize);



/*
NAME: MyMalloc.
DESCRIPTION: This function allocated memory in given memory block.
INPUT: _memory - block size of memory.
        _requiredBlockSize the size(in byte) of the desired storage.
OUTPUT: begin address of allocated storage on success.
        NULL if _memory is null or 
        there is not enough space for allocation or
        if _requiredBlockSize = 0.
NOTE: Every allocation give _requiredBlockSize bytes to the
user, but reserves _requiredBlockSize+8 bytes from _memory.
 */
void* MyMalloc(void* _memory, size_t _requiredBlockSize);


/*
NAME: MyFree.
DESCRIPTION: This function free allocated memory in the memory block.
INPUT: _myBlock - begin address of memory block for free.
OUTPUT: non.
NOTE: !!! Undefine behavior for given wrong address !!! 
 */
void MyFree(void* _myBlock);

#endif /* __MY_MALLOC_H__ */