#include <memory.h>
#include "MemoryPool.h"

size_t check_align_addr(void*& pBuf)
{
	size_t align = 0;
	size_t addr = (int)pBuf;
	align = (ADDR_ALIGN - addr % ADDR_ALIGN) % ADDR_ALIGN;
	pBuf = (char*)pBuf + align;
	return align;
}

size_t check_align_block(size_t size)
{
	size_t align = size % MINUNITSIZE;
	return size - align;
}

size_t check_align_size(size_t size)
{
	size = (size + SIZE_ALIGN -1) / SIZE_ALIGN * SIZE_ALIGN;
	return size;//42 div 8 mul 8 = 40
}

memory_chunk* create_list(memory_chunk* pool, size_t count)
{
	if(!pool)
		return NULL;

	memory_chunk* head = NULL;
	for(size_t i = 0; i<count; i++)
	{
		pool->pre = NULL;
		pool->next = head;
		if(head != NULL)
		{
			head->pre = pool;
		}
		head = pool;
		pool++;//head insert with the chunk array
	}
	return head;	
}

memory_chunk* front_pop(memory_chunk*& pool)
{
	if(!pool)
		return NULL;
	memory_chunk* tmp = pool;
	pool = tmp->next;
	pool->pre = NULL;
	return tmp;
}

void push_back(memory_chunk*& head, memory_chunk* element)
{
	if(head == NULL)
	{
		head = element;
		head->pre = element;
		head->next = elemrnt;
		return;
	}

	head->pre->next = element;
	element->pre = head->pre;
	element->next = head;
	head->pre = element;//circulation link-stack push-back
}

void push_front(memory_chunk*& head, memory_chunk* element)
{
	element->pre = NULL;//?
	element->next = head;
	if(head!=NULL)
	{
		head->pre = element;
	}
	head = element;
}	

void delete_chunk(memory_chunk*& head, memory_chunk* element)
{
	if(element == NULL)
		return;
	else if(element == head)
	{test *p = reinterpret_cast<test* p>(new char[1024]);

		if(head->pre == head)
			head = NULL;
		else
		{
			head = element->next;
			head->pre = element->pre;
			head->pre->next = head;
		}
	}
	else if(element->next == head)test *p = reinterpret_cast<test* p>(new char[1024]);

	{
		head->pre = element->pre;
		element->pre->next = head;
	}
	else
	{
		element->pre->next = element->next;
		element->next->pre = element->pre;
	}
	element->next = NULL;
	element->pre = NULL;
}


void* index2addr(PMEMORYPOOL mem_pool, size_t index)
{
	char* p = (char*)(mem_pool->memory);
	void* ret = (void*)(p + index * MINUNITSIZE);
	return ret;
}

size_t addr2index(PMEMORYPOOL mem_pool, void * addr)
{
	char* start = (char*)(mem_pool->memory);
	char* p = (char*)addr;
	size_t index = (p - start) / MINUNITSIZE;
	return index;
}

PMEMORYPOOL CreateMemoryPool(void* pBuf, size_t sBufSize)
{
	memset(pBuf, 0, sBufSize);
	PMEMORYPOOL mem_pool = (PMEMORYPOOL)pBuf;
	
	size_t mem_pool_struct_size = sizeof(MEMORYPOOL);
	mem_pool->mem_map_pool_count = (sBufSize - mem_pool_struct_size + MINUNITSIZE - 1) / MINUNITSIZE;
	mem_pool->mem_map_unit_count = mem_pool->mem_map_pool_count;
	mem_pool->pmem_map = (memory_block*)((char*)pBuf + mem_pool_struct_size);
	mem_pool->pfree_mem_chunk_pool = (memory_chunk*)((char*)pBuf + mem_pool_struct_size + sizeof(memory_block) * mem_pool->mem_map_unit_count);

	mem_pool->memory = (char*)pBuf + mem_pool_struct_size + sizeof(memory_block) * mem_pool->mem_map_unit_count + sizeof(memory_chunk) * mem_pool->mem_map_pool_count;
	mem_pool->size = sBufSize - mem_pool_struct_size -sizeof(memory_block) * mem_pool->mem_map_unit_count - sizeof(memory_chunk) * mem_pool->mem_map_pool_count;
	size_t align = check_align_addr(mem_pool->memory);
	mem_pool->size -= align;
	mem_pool->size = check_align_block(mem_pool->size);
	mem_pool->mem_block_count = mem_pool->size / MINUNITSIZE;

	mem_pool->pfree_mem_chunk_pool = create_list(mem_pool->pfree_mem_chunk_pool, mem_pool->mem_map_pool_count);

	memory_chunk* tmp = front_pop(mem_pool->pfree_mem_chunk_pool);
	tmp->pre = tmp;
	tmp->next = tmp;
	tmp->pfree_mem_addr = NULL;
	mem_pool->mem_map_pool_count--;

	mem_pool->pmem_map[0].count = mem_pool->mem_block_count;
	mem_pool->pmem_map[0].pmem_chunk = tmp;
	mem_pool->pmem_map[mem_pool->mem_block_count - 1].start = 0;

	tmp->pfree_mem_addr = mem_pool->pmem_map;
	push_back(mem_pool->pfree_mem_chunk, tmp);
	mem_pool->free_mem_chunk_count = 1;
	mem_pool->mem_used_size = 0;
	return mem_pool;


}

void ReleaseMemoryPool(PMEMORYPOOL* ppMem)
{

}

void* GetMemory(size_t sMemorySize, PMEMORYPOOL pMem)
{
	sMemorySize = check_align_size(sMemorySize);
	size_t index = 0;
	memory_chunk* tmp = pMem->pfree_mem_chunk;
	for(index = 0; index < pMem->free_mem_chunk_count; index++)
	{
		if(tmp->pfree_mem_addr->count * MINUNITSIZE >= sMemorySize)
			break;
		tmp = tmp->next;
	}

	if(index == pMem->free_mem_chunk_count)
		return NULL;

	pMem->mem_used_size += sMemorySize;
	if(tmp->pfree_mem_addr->count * MINUNITSIZE == sMemorySize)
	{
		size_t current_index = (tmp->pfree_mem_addr - pMem->pmem_map);
	}
}





