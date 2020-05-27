#ifndef _MEMORYPOOL_H_
#define _MEMORYPOOL_H_
#include <stdlib.h>
#define MINUNITSIZE 64
#define ADDR_ALIGN 8
#define SIZE_ALIGN MINUNITSIZE
struct memory_chunk;
typedef struct memory_block
{
	size_t count;
	size_t start;
	memory_chunk* pmem_chunk;
}memory_block;

typedef struct memory_chunk
{
	memory_block* pfree_mem_addr;
	memory_chunk* pre;
	memory_chunk* next;//linklist

}memory_chunk;

typedef struct MEMORYPOOL
{
	void *memory;
	size_t size;
	memory_block* pmem_map;
	memory_chunk* pfree_mem_chunk;
	memory_chunk* pfree_mem_chunk_pool;
	size_t mem_used_size;
	size_t mem_map_pool_count;
	size_t free_mem_chunk_count;
	size_t mem_map_unit_count;
	size_t mem_block_count;
}MEMORYPOOL, *PMEMORYPOOL;

PMEMORYPOOL CreateMemoryPool(void* pBuf, size_t sBufSize);

void ReleaseMemoryPool(PMEMORYPOOL* ppMem);

void* GetMemory(size_t sMemorySize, PMEMORYPOOL pMem);

void FreeMemory(void *ptrMemoryBlock, PMEMORYPOOL pMem);

#endif

