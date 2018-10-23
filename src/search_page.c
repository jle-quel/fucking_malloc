/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_page.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:45:38 by jle-quel          #+#    #+#             */
/*   Updated: 2018/10/23 10:48:17 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allocation.h>

static inline t_meta	*get_block(t_meta *meta_ptr, size_t const size)
{
	void	*ptr;

	ptr = NULL;
	if (meta_ptr->size >= (size + sizeof(t_meta) + MEMORY_ALIGN))
	{
		ptr = (void *)meta_ptr;
		ptr += (sizeof(t_meta) + size);
		create_meta(TRUE, meta_ptr->size - (size + sizeof(t_meta)),
		ptr, meta_ptr->next);
		meta_ptr->next = ptr;
	}
	meta_ptr->size = size;
	meta_ptr->free = FALSE;
	return (meta_ptr);
}

static t_meta			*find_block(t_header *header_ptr, size_t const size)
{
	t_meta *meta_ptr;
	t_meta *result;

	meta_ptr = (t_meta *)header_ptr;
	result = NULL;
	while (meta_ptr)
	{
		if (meta_ptr->free && meta_ptr->size >= size)
			return (get_block(meta_ptr, size));
		meta_ptr = meta_ptr->next;
	}
	return (NULL);
}

void					*search_page(uint8_t const allocation_type,
						size_t const size)
{
	t_header	*header_ptr;
	void		*result;

	header_ptr = *arena();
	result = NULL;
	while (header_ptr)
	{
		if (header_ptr->type == allocation_type)
		{
			if ((result = find_block(header_ptr + 1, size)))
				return ((void *)result);
		}
		header_ptr = header_ptr->next;
	}
	return (NULL);
}
