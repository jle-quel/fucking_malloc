#include "allocation.h"

////////////////////////////////////////////////////////////////////////////////
/// STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static inline size_t get_page_size(uint8_t const alloc_type, size_t const size)
{
	if (alloc_type & TINY)
		return TINY_PRE_ALLOC;
	else if (alloc_type & SMALL)
		return SMALL_PRE_ALLOC;
	else
		return (size + sizeof(t_header)) + (sizeof(t_meta) * 2);
}

static void add_page(void *ptr)
{
	t_header *new_ptr = (t_header *)ptr;
	t_header *header_ptr;

	if ((header_ptr = *arena()))
	{
		while (header_ptr->next)
			header_ptr = header_ptr->next;
		header_ptr->next = new_ptr;
	}
	else
		*arena() = new_ptr;
}

////////////////////////////////////////////////////////////////////////////////
/// PUBLIC FUNCTION
////////////////////////////////////////////////////////////////////////////////

void *new_page(uint8_t const allocation_type, size_t const size)
{
	size_t const page_size = get_page_size(allocation_type, size);
	void *ptr = NULL;
	void *result = NULL;
	void *next = NULL;

	if ((ptr = mmap(NULL, page_size, PROT_FLAG, MAP_FLAG, -1, 0)) == MAP_FAILED)
	{
		errno = ENOMEM;
		return NULL;
	}

	result = ptr + sizeof(t_header);
	next = result + (sizeof(t_meta) + size);

	create_header(allocation_type, page_size, ptr);
	create_meta(FALSE, size, result, next);
	create_meta(TRUE, page_size - (((sizeof(t_meta) * 2) + sizeof(t_header)) + size), next, NULL);
	add_page(ptr);

	return result;
}