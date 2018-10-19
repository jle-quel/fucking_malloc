#include <allocation.h>

////////////////////////////////////////////////////////////////////////////////
/// STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void *get_block(t_header *header_ptr, size_t const size)
{
	t_meta *meta_ptr = NULL;
	t_meta *result = NULL;
	void *ptr = NULL;

	meta_ptr = (t_meta *)header_ptr;

	while (meta_ptr)
	{
		if (meta_ptr->free && meta_ptr->size >= size)
		{
			if (meta_ptr->size >= (size + sizeof(t_meta) + MEMORY_ALIGN))
			{
				ptr = (void *)meta_ptr;
				ptr += (sizeof(t_meta) + size);
				create_meta(TRUE, (meta_ptr->size - size) - sizeof(t_meta), ptr, meta_ptr->next);
				meta_ptr->next = ptr;
			}

			meta_ptr->size = size;
			meta_ptr->free = FALSE;
			return (void *)meta_ptr;
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