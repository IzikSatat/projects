#include <stdlib.h>
#include "my_malloc.h"

#define ADDRESS_SIZE 8
#define MIN_MEMORY_SIZE 32

/* helper function for MyMalloc. Find if there is space and where*/
static size_t FindSpace(void* _memory, long _requiredBlockSize);
/* helper function for FindSpace*/
static long Absolute(long _num);


void MyMallocInit(void* _memory, size_t _memorySize)
{
    if(_memory == NULL
     || _memorySize < MIN_MEMORY_SIZE
     || (_memorySize % ADDRESS_SIZE) !=  0)
     {
         return;
     }

    ((long*)_memory)[0] = _memorySize; /* "general metadata */
    ((long*)_memory)[1] = _memorySize - 3*ADDRESS_SIZE; /* actual metadata, 3 adderss use for setting*/
    ((long*)_memory)[_memorySize/ADDRESS_SIZE - 1] = 0; /* zero is flage of end*/
}



void* MyMalloc(void* _memory, size_t _requiredBlockSize)
{
    long temp = 0;
    size_t index = 1;

    if(_memory == NULL || _requiredBlockSize == 0)
    {
        return NULL;
    }
    
    if(_requiredBlockSize % ADDRESS_SIZE != 0)
    {
         /* alignment 8 BYTE*/
        _requiredBlockSize += ADDRESS_SIZE - _requiredBlockSize % ADDRESS_SIZE;
    }

    index = FindSpace(_memory, _requiredBlockSize);
    temp = ((long*)_memory)[index]; /* temp get the size of next free bytes */

    if(index == 0) /* if there is no space */
    {
        return NULL;
    }

    ((long*)_memory)[index] = -1 * (_requiredBlockSize); /*negative indicates this space in use */

    if(temp - _requiredBlockSize > 0) /* if next metadata is not zero flag*/
    {
        /* set the next metadata*/
        ((long*)_memory)[index + _requiredBlockSize/ADDRESS_SIZE + 1] 
     = temp - (_requiredBlockSize + ADDRESS_SIZE); /* +1 for metadata*/
    }

    return &((long*)_memory)[index + 1];
}



void MyFree(void* _myBlock)
{
    long temp  = 0, *ptr = _myBlock;

    if(_myBlock == NULL)
    {
        return;
    }

    ptr--;

    temp = *ptr;

    if(0 <= temp)
    {
        return;
    }

    /* if the next block is free*/
    if(0 < ptr[Absolute(temp)/ADDRESS_SIZE + 1])
    {
        temp -= ptr[Absolute(temp)/ADDRESS_SIZE + 1];
        temp -= ADDRESS_SIZE;
    }

    temp = Absolute(temp);

    *ptr = temp;
}

static long Absolute(long _num)
{
    if(_num < 0)
    {
        _num = -1 * _num;
    }

    return _num;
}



static size_t FindSpace(void* _memory, long _requiredBlockSize)
{
    long temp = 0;
    size_t index = 1;

    temp = ((long*)_memory)[index];

    while((temp < _requiredBlockSize)
         && temp != 0) /* while there is no space and its not the end*/
    {
        index = index + Absolute(temp/ADDRESS_SIZE) + 1; /* +1 for metadata*/
        temp = ((long*)_memory)[index];
    }

    if(temp == 0) /* if there is no  space*/
    {
        index = 0;;
    }

    return index;
}
