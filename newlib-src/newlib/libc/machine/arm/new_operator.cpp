//maps a proper collection garbage environment required by Newlib -- TGDS

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

extern "C" void *malloc(size_t  nbytes);
extern "C" void *realloc(void *aptr, size_t nbytes);
extern "C" void *reallocf(void * aptr , size_t nbytes);	
extern "C" void free(void *aptr);

void *operator new (unsigned nSize)
{
	return malloc (nSize);
}

void *operator new[] (unsigned nSize)
{
	return malloc (nSize);
}

void operator delete (void *pBlock)
{
	free (pBlock);
}

void operator delete[] (void *pBlock)
{
	free (pBlock);
}

void operator delete (void *pBlock, unsigned nSize)
{
	free (pBlock);
}

void operator delete[] (void *pBlock, unsigned nSize)
{
	free (pBlock);
}
