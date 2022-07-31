#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

#define TYPICALLY_SIZE 1000
#define ADDRESS_SIZE 8

void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test7();
void Test8();
void Test9();
void Test10();
void Test11();
void Test12();
void Test13();
void Test14();
void Test15();
void Test16();
void Test17();
void Test18();
void Test19();
void Test20();
void Test21();
void Test22();
void Test23();
void Test24();


int main(int argc, char const *argv[])
{
    /* MyMallocInit tests*/
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
    Test11();
    Test12();
    Test13();
    Test14();
    Test15();
    Test16();
    Test17();
    Test18();
    Test19();
    Test20();
    Test21();
    Test22();
    Test23();
    Test24();

    return 0;
}

/* Test1 check MyMallocInit when memoryBlock is null*/
void Test1()
{
    void* memoryBlock = NULL;

    MyMallocInit(memoryBlock, TYPICALLY_SIZE);

    if(memoryBlock != NULL)
    {
        printf("Test1  FAIL\n");
    }
    else
    {
        printf("Test1  SUCCESS\n");
    }
    
}

/* Test2 check MyMallocInit when blockSize is 0*/
void Test2()
{
    void* memoryBlock = NULL;

    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test2  COULDN'T RUN\n");
        return;
    }

    ((long*)memoryBlock)[0] = 19;
    ((long*)memoryBlock)[1] = -13;
    ((long*)memoryBlock)[TYPICALLY_SIZE - 1] = 23;

    MyMallocInit(memoryBlock, 0);

    if(((long*)memoryBlock)[0] != 19
    || ((long*)memoryBlock)[1] != -13
    || ((long*)memoryBlock)[TYPICALLY_SIZE - 1] != 23)
    {
        printf("Test2  FAIL\n");
    }
    else
    {
        printf("Test2  SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test3 check MyMallocInit when blockSize is not in multiple of 8*/
void Test3()
{
    void* memoryBlock = NULL;

    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test3  COULDN'T RUN\n");
        return;
    }

    ((long*)memoryBlock)[0] = 19;
    ((long*)memoryBlock)[1] = -13;
    ((long*)memoryBlock)[TYPICALLY_SIZE - 1] = 23;

    MyMallocInit(memoryBlock, 50);

    if(((long*)memoryBlock)[0] != 19
    || ((long*)memoryBlock)[1] != -13
    || ((long*)memoryBlock)[TYPICALLY_SIZE - 1] != 23)
    {
        printf("Test3  FAIL\n");
    }
    else
    {
        printf("Test3  SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test4 check MyMallocInit when blockSize = 32 (minimum size)*/
void Test4()
{
    void* memoryBlock = NULL;
    size_t blockSize = 32;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test4  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);

    if(((long*)memoryBlock)[0] != 32
    || ((long*)memoryBlock)[1] != 8
    || ((long*)memoryBlock)[blockSize - 1] != 0)
    {
        printf("Test4  FAIL\n");
    }
    else
    {
        printf("Test4  SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test5 check MyMallocInit when blockSize = 1000 (correct number)*/
void Test5()
{
    void* memoryBlock = NULL;
    size_t blockSize = TYPICALLY_SIZE;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test5  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);

    if(((long*)memoryBlock)[0] != 1000
    || ((long*)memoryBlock)[1] != 976
    || ((long*)memoryBlock)[blockSize/ADDRESS_SIZE - 1] != 0)
    {
        printf("Test5  FAIL\n");
    }
    else
    {
        printf("Test5  SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test6 check MyMallocInit when blockSize = 56 (correct number)*/
void Test6()
{
    void* memoryBlock = NULL;
    size_t blockSize = 56;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test6  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);

    if(((long*)memoryBlock)[0] != blockSize
    || ((long*)memoryBlock)[1] != 32
    || ((long*)memoryBlock)[blockSize - 1] != 0)
    {
        printf("Test6  FAIL\n");
    }
    else
    {
        printf("Test6  SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test7 check MyMalloc when memoryBlock is null  */
void Test7()
{
    void* allocated = NULL;

    allocated = MyMalloc(NULL, 32);

    if(allocated != NULL)
    {
        printf("Test7  FAIL\n");
    }
    else
    {
        printf("Test7  SUCCESS\n");
    }

}

/* Test8 check MyMalloc when  _requiredBlockSize = 0 */
void Test8(         )
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 200;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test8  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 0);

    if(allocated != NULL)
    {
        printf("Test8  FAIL\n");
    }
    else
    {
        printf("Test8  SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test9 check MyMalloc when  _requiredBlockSize >  blockSaize*/
void Test9()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 200;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test9  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, blockSize + 8);

    if(allocated != NULL)
    {
        printf("Test9  FAIL\n");
    }
    else
    {
        printf("Test9  SUCCESS\n");
    }

    free(memoryBlock);
}
/* Test10 check MyMalloc when blockSaize = 32 and _requiredBlockSize = 8 */
void Test10()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 32;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test10  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 8);

    if(allocated != (long*)memoryBlock + 2
    || ((long*)allocated)[1] != 0)
    {
        printf("Test10 FAIL\n");
    }
    else
    {
        printf("Test10 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test11 check MyMalloc when blockSaize = 32 and 
    _requiredBlockSize = blockSaize -16 */
void Test11()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 32;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test11  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 16);

    if(allocated != NULL)
    {
        printf("Test11 FAIL\n");
    }
    else
    {
        printf("Test11 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test12 check MyMalloc when blockSaize = 32 and 
    _requiredBlockSize = blockSaize -8 */
void Test12()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 32;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test12  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 24);

    if(allocated != NULL)
    {
        printf("Test12 FAIL\n");
    }
    else
    {
        printf("Test12 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test13 check MyMalloc when blockSaize = _requiredBlockSize */
void Test13()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 560;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test13  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, blockSize);

    if(allocated != NULL)
    {
        printf("Test13 FAIL\n");
    }
    else
    {
        printf("Test13 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test14 check MyMalloc for simple and correct */
void Test14()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 560;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test14  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 80);

    if(allocated == NULL
    || ((long*)memoryBlock)[1] != -80
    || ((long*)allocated)[80/ADDRESS_SIZE] != 448
    || ((long*)allocated)[448/ADDRESS_SIZE] != 0)
    {
        printf("Test14 FAIL\n");
    }
    else
    {
        printf("Test14 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test15 check MyMalloc for 0 < _requiredBlockSize < 8 */
void Test15()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 560;
    size_t _requiredBlockSize = 6;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test15  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, _requiredBlockSize);

    if(allocated == NULL
    || ((long*)memoryBlock)[1] != -8
    || ((long*)allocated)[8/ADDRESS_SIZE] != 520
    || ((long*)allocated)[520/ADDRESS_SIZE] != 0)
    {
        printf("Test15 FAIL\n");
    }
    else
    {
        printf("Test15 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test16 check MyMalloc for 8 < _requiredBlockSize but not in multiple of 8 */
void Test16()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 800;
    size_t _requiredBlockSize = 54;
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test16  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, _requiredBlockSize);

    if(allocated == NULL
    || ((long*)memoryBlock)[1] != -56
    || ((long*)allocated)[56/ADDRESS_SIZE] != 712
    || ((long*)allocated)[712/ADDRESS_SIZE] != 0)
    {
        printf("Test16 FAIL\n");
    }
    else
    {
        printf("Test16 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test17 check use MyMalloc twice when the seconed allocated 
    is exactly the space with metadaat */
void Test17()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 104;
    
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test17  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 40);
    allocated = MyMalloc(memoryBlock, 32);

    if(allocated == NULL
    || ((long*)memoryBlock)[7] != -32
    || ((long*)allocated)[32/ADDRESS_SIZE] != 0)
    {
        printf("Test17 FAIL\n");
    }
    else
    {
        printf("Test17 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test18 check use MyMalloc twice when the seconed allocated 
    is exactly the space without metadata */
void Test18()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 104;
    
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test18  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 40);
    allocated = MyMalloc(memoryBlock, 40);

    if(allocated != NULL)
    {
        printf("Test18 FAIL\n");
    }
    else
    {
        printf("Test18 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test19 check use MyMalloc twice when there is no space
for the seconed allocation */ 
void Test19()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 104;
    
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test19  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 40);
    allocated = MyMalloc(memoryBlock, 48);

    if(allocated != NULL)
    {
        printf("Test19 FAIL\n");
    }
    else
    {
        printf("Test19 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test20 check use MyMalloc twice when there is no space
for the metadata of the seconed allocation */ 
void Test20()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 104;
    
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test20  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 72);
    allocated = MyMalloc(memoryBlock, 8);

    if(allocated != NULL
    || ((long*)memoryBlock)[12] != 0
    || ((long*)memoryBlock)[1] != -72
    || ((long*)memoryBlock)[11] != 0)
    {
        printf("Test20 FAIL\n");
    }
    else
    {
        printf("Test20 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test21 check MyFree for null */ 
void Test21()
{ 
    MyFree(NULL);

    printf("Test21 SUCCESS\n");
    
}

/* Test22 check MyFree for simple free */ 
void Test22()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 560;
    
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test22  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    allocated = MyMalloc(memoryBlock, 200);
    MyFree(allocated);

    if(((long*)memoryBlock)[1] != 536
    || ((long*)memoryBlock)[69] != 0)
    {
        printf("Test22 FAIL\n");
    }
    else
    {
        printf("Test22 SUCCESS\n");
    }

    free(memoryBlock);
}

/* Test23 check MyFree when free block between two allocated block*/ 
void Test23()
{
    void* memoryBlock = NULL;
    void* allocated = NULL;
    size_t blockSize = 560;
    
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test23  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    MyMalloc(memoryBlock, 32);
    allocated = MyMalloc(memoryBlock, 32);
    MyMalloc(memoryBlock, 32);
    MyFree(allocated);

    if(((long*)memoryBlock)[1] != -32
    || ((long*)memoryBlock)[6] != 32
    || ((long*)memoryBlock)[11] != -32
    || ((long*)memoryBlock)[69] != 0)
    {
        printf("Test23 FAIL\n");
    }
    else
    {
        printf("Test23 SUCCESS\n");
    }

    free(memoryBlock);
}

	/* Test24 check MyFree for free block after free anouther block*/ 
void Test24()
{
    void* memoryBlock = NULL;
    void* allocated1 = NULL;
    void* allocated2 = NULL;
    size_t blockSize = 560;
    
    memoryBlock = malloc(TYPICALLY_SIZE);

    if(memoryBlock == NULL)
    {
        printf("Test24  COULDN'T RUN\n");
        return;
    }

    MyMallocInit(memoryBlock, blockSize);
    MyMalloc(memoryBlock, 32);
    allocated1 = MyMalloc(memoryBlock, 32);
    allocated2 = MyMalloc(memoryBlock, 32);
    MyFree(allocated2);
    MyFree(allocated1);

    if(((long*)memoryBlock)[1] != -32
    || ((long*)memoryBlock)[6] != 496
    || ((long*)memoryBlock)[11] != 456
    || ((long*)memoryBlock)[69] != 0)
    {
        printf("Test24 FAIL\n");
    }
    else
    {
        printf("Test24 SUCCESS\n");
    }

    free(memoryBlock);
}