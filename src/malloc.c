#include <allocation.h>

////////////////////////////////////////////////////////////////////////////////
/// STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static inline uint8_t get_allocation_type(const size_t size)
{
	if (size <= TINY_MAX)
		return TINY;
	else if (size <= SMALL_MAX)
		return SMALL;
	else
		return LARGE;
}

////////////////////////////////////////////////////////////////////////////////
/// PUBLIC FUNCTION
////////////////////////////////////////////////////////////////////////////////

void *malloc(size_t size)
{
	uint8_t const allocation_type = get_allocation_type(size);
	void *ptr = NULL;

	if (size == 0)
		size = 1;

	size += (MEMORY_ALIGN - (size + sizeof(t_meta)) % MEMORY_ALIGN);

	if ((ptr = search_page(allocation_type, size)))
		return (ptr + sizeof(t_meta));
	if ((ptr = new_page(allocation_type, size)))
		return ptr + sizeof(t_meta);

	return NULL;
}
