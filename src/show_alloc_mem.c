#include "allocation.h"

////////////////////////////////////////////////////////////////////////////////
/// STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

static void print_line(t_meta const *meta_ptr)
{
	unsigned long long const beg = (unsigned long long const)meta_ptr;
	unsigned long long const end = (unsigned long long const)meta_ptr->next;

	print_str(meta_ptr->free ? "▹" : "▸");
	print_str("  ");
	print_ptr(beg);
	print_str(" - ");
	print_ptr(end);
	print_str(" : ");
	print_num(end - beg);
	print_str(" octets\n");
}

static void print_header(t_header const *header_ptr, uint8_t const alloc_type)
{
	char *str;

	if (header_ptr == NULL)
		return;

	if (alloc_type & TINY)
		str = "\e[31mTINY\e[0m : ";
	else if (alloc_type & SMALL)
		str = "\e[32mSMALL\e[0m : ";
	else
		str = "\e[34mLARGE\e[0m : ";

	print_str(str);
	print_ptr((unsigned long long)header_ptr);
	print_str("\n");
}

static size_t print_page(t_header *header_ptr)
{
	t_meta *meta_ptr = (t_meta *)header_ptr;
	size_t total = 0;

	while (meta_ptr)
	{
		if (meta_ptr->size)
		{
			print_line(meta_ptr);
			total += meta_ptr->size;
		}
		meta_ptr = meta_ptr->next;
	}

	return (total);
}

////////////////////////////////////////////////////////////////////////////////
/// PUBLIC FUNCTION
////////////////////////////////////////////////////////////////////////////////

void show_alloc_mem(void)
{
	uint8_t alloc_type = 1;
	t_header *header_ptr;
	t_header *tmp;
	size_t total = 0;

	if ((header_ptr = *arena()) == NULL)
		return;
	tmp = header_ptr;

	while (alloc_type <= 4)
	{
		if (header_ptr->type & alloc_type)
			print_header(header_ptr, alloc_type);
		while (header_ptr)
		{
			if (header_ptr->type & alloc_type)
				total += print_page(header_ptr + 1);
			header_ptr = header_ptr->next;
		}
		header_ptr = tmp;
		alloc_type <<= 1;
	}

	print_str("\nTotal : ");
	print_num(total);
	print_str("\n");
}