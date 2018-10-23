/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:42:09 by jle-quel          #+#    #+#             */
/*   Updated: 2018/10/23 10:45:24 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation.h"

static void	print_header(t_header const *header_ptr)
{
	char	*str;

	if (header_ptr == NULL)
		return ;
	if (header_ptr->type == TINY)
		str = "\e[31mTINY\e[0m : ";
	else if (header_ptr->type == SMALL)
		str = "\e[32mSMALL\e[0m : ";
	else
		str = "\e[34mLARGE\e[0m : ";
	print_str(str);
	print_ptr((unsigned long long)header_ptr);
	print_str("\n");
}

static void	print_line(const t_meta *meta_ptr)
{
	void	*beg;
	void	*end;

	beg = (void *)meta_ptr;
	end = (void *)meta_ptr->next;
	print_str(meta_ptr->free ? "▹" : "▸");
	print_str("  ");
	print_ptr((unsigned long long)beg);
	print_str(" - ");
	print_ptr((unsigned long long)end);
	print_str(" : ");
	print_num((unsigned long long)meta_ptr->size);
	print_str(" octets\n");
}

static void	print_total(size_t const total)
{
	print_str("\nTotal : ");
	print_num(total);
	print_str("\n");
}

void		show_alloc_mem(void)
{
	t_header	*header_ptr;
	t_header	*tmp;
	t_meta		*meta_ptr;
	size_t		total;

	header_ptr = *arena();
	total = 0;
	while (header_ptr)
	{
		print_header(header_ptr);
		tmp = header_ptr + 1;
		meta_ptr = (t_meta *)tmp;
		while (meta_ptr)
		{
			if (meta_ptr->next)
			{
				total += meta_ptr->size;
				print_line(meta_ptr);
			}
			meta_ptr = meta_ptr->next;
		}
		header_ptr = header_ptr->next;
	}
	print_total(total);
}
