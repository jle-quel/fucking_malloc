/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:55:41 by jle-quel          #+#    #+#             */
/*   Updated: 2018/10/23 10:57:57 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allocation.h>

static inline void	defragment_memory(t_meta *meta_ptr)
{
	t_meta	*tmp;
	size_t	size;

	tmp = meta_ptr;
	size = 0;
	meta_ptr->free = TRUE;
	while (tmp && tmp->free)
	{
		size += sizeof(t_meta) + tmp->size;
		tmp = tmp->next;
	}
	meta_ptr->size = size - sizeof(t_meta);
	meta_ptr->next = tmp ? tmp : NULL;
}

static bool			search_ptr(void *ptr, t_header *header_ptr)
{
	t_meta *meta_ptr;
	t_meta *free_ptr;

	meta_ptr = (t_meta *)header_ptr;
	ptr -= sizeof(t_meta);
	free_ptr = (t_meta *)ptr;
	while (meta_ptr)
	{
		if (meta_ptr == ptr)
		{
			defragment_memory(meta_ptr);
			return (true);
		}
		meta_ptr = meta_ptr->next;
	}
	return (false);
}

void				free(void *ptr)
{
	t_header	*header_ptr;
	t_header	*free_ptr;

	header_ptr = *arena();
	free_ptr = (t_header *)ptr;
	while (header_ptr)
	{
		if (free_ptr > header_ptr)
		{
			if (search_ptr(ptr, header_ptr + 1) == true)
				return ;
		}
		header_ptr = header_ptr->next;
	}
}
