#include <allocation.h>

////////////////////////////////////////////////////////////////////////////////
/// TOOL FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static inline t_meta *free_block(t_meta *meta_ptr, size_t const size)
{
	if (meta_ptr->size >= size)
	{
		meta_ptr->free = FALSE;
		return meta_ptr;
	}

	return NULL;
}

static inline t_meta *alloc_block(t_meta *meta_ptr, size_t const size)
{
	void *ptr;

	if (meta_ptr->size >= size + (sizeof(t_meta)))
	{
		ptr = (void *)meta_ptr;
		ptr += sizeof(t_meta) + size;
		create_meta(TRUE, meta_ptr->size - (size + sizeof(t_meta)), ptr, NULL);
		meta_ptr->size = size;
		meta_ptr->free = FALSE;
		return meta_ptr;
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
/// STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void *get_block(t_header *header_ptr, size_t const size)
{
	t_meta *meta_ptr;
	t_meta *result = NULL;

	meta_ptr = (t_meta *)header_ptr;

	while (meta_ptr)
	{
		if (meta_ptr->free)
		{
			if ((result = meta_ptr->next ? free_block(meta_ptr, size) : alloc_block(meta_ptr, size)))
				return (void *)result;
		}
		meta_ptr = meta_ptr->next;
	}

	return (NULL);
}

////////////////////////////////////////////////////////////////////////////////
/// PUBLIC FUNCTION
////////////////////////////////////////////////////////////////////////////////

void *search_page(const uint8_t allocation_type, const size_t size)
{
	t_header *header_ptr = NULL;
	void *result = NULL;

	header_ptr = *arena();

	if (allocation_type == LARGE)
		return NULL;

	while (header_ptr)
	{
		if (header_ptr->type == allocation_type)
		{
			if ((result = get_block(header_ptr + 1, size)))
				return result;
		}
		header_ptr = header_ptr->next;
	}

	return NULL;
}