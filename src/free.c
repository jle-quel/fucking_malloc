#include <allocation.h>

////////////////////////////////////////////////////////////////////////////////
/// TOOL FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static inline void defragment_memory(t_meta *meta_ptr)
{
	t_meta *tmp = meta_ptr;
	size_t size = 0;

	meta_ptr->free = TRUE;

	while (tmp && tmp->free)
	{
		size += sizeof(t_meta) + tmp->size;
		tmp = tmp->next;
	}

	meta_ptr->size = size - sizeof(t_meta);
	meta_ptr->next = tmp ? tmp : NULL;
}

static inline void delete_page(t_header *header_ptr, t_header *old_ptr)
{
}

////////////////////////////////////////////////////////////////////////////////
/// STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static bool search_ptr(void *ptr, t_header *header_ptr, t_header *old_ptr)
{
	void *cast = (void *)header_ptr;
	cast += sizeof(t_header);
	t_meta *meta_ptr = (t_meta *)cast;
	ptr -= sizeof(t_meta);
	t_meta *free_ptr = (t_meta *)ptr;

	while (meta_ptr)
	{
		if (meta_ptr == ptr)
		{
			header_ptr->type == LARGE ? delete_page(header_ptr, old_ptr) : defragment_memory(meta_ptr);
			return true;
		}
		meta_ptr = meta_ptr->next;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
/// PUBLIC FUNCTION
////////////////////////////////////////////////////////////////////////////////

void free(void *ptr)
{
	t_header *header_ptr = *arena();
	t_header *free_ptr = (t_header *)ptr;
	t_header *old_ptr = NULL;

	while (header_ptr)
	{
		if (free_ptr > header_ptr)
		{
			if (search_ptr(ptr, header_ptr, old_ptr) == true)
				return;
		}
		old_ptr = header_ptr;
		header_ptr = header_ptr->next;
	}
	return;
}