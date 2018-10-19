#include <allocation.h>

void _putstr(char *str)
{
	write(1, "0x", 2);
	while (*str)
	{
		write(1, (const void *)&(*str), 1);
		str++;
	}
	write(1, "\n", 1);
}

void ft_putaddress(void *ptr)
{
	unsigned long long llu_ptr;
	static char hexa_tab[] = "0123456789abcdef";
	static char hexa[10];
	int i;

	llu_ptr = (unsigned long long)ptr;
	bzero(hexa, 10);
	i = 8;
	while (llu_ptr)
	{
		hexa[i] = hexa_tab[llu_ptr % 16];
		llu_ptr = llu_ptr / 16;
		i--;
	}
	_putstr(hexa);
}

////////////////////////////////////////////////////////////////////////////////
/// TOOL FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static inline void defragment_memory(t_meta *meta_ptr)
{
	size_t size = 0;
	t_meta *tmp = meta_ptr;

	meta_ptr->free = TRUE;

	while (tmp && tmp->free)
	{
		size += sizeof(t_meta) + tmp->size;
		// write(1, "META\n", 5);
		// ft_putaddress(tmp);
		// ft_putaddress(tmp->next);
		// write(1, "\n", 1);
		tmp = tmp->next;
	}

	if (size)
		meta_ptr->size = size - sizeof(t_meta);
}

////////////////////////////////////////////////////////////////////////////////
/// STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static void search_ptr(void *ptr, t_header *header_ptr)
{
	t_header *hd = header_ptr + 1;
	t_meta *meta_ptr = (t_meta *)hd;
	t_meta *tmp = (t_meta *)ptr;

	while (meta_ptr)
	{
		if (tmp == meta_ptr)
		{
			if (header_ptr->type == LARGE)
				;
			else
			{
				defragment_memory(meta_ptr);
			}
			return;
		}
		meta_ptr = meta_ptr->next;
	}
}

////////////////////////////////////////////////////////////////////////////////
/// PUBLIC FUNCTION
////////////////////////////////////////////////////////////////////////////////

void free(void *ptr)
{
	t_header *header_ptr = *arena();
	ptr -= sizeof(t_meta);
	t_header *tmp = (t_header *)ptr;

	while (header_ptr)
	{
		// if (tmp > header_ptr)
		// {
		// search_ptr(ptr, header_ptr);
		// return;
		// }
		header_ptr = header_ptr->next;
	}
}
