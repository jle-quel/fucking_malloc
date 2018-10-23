/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:25:22 by jle-quel          #+#    #+#             */
/*   Updated: 2018/10/23 10:41:22 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation.h"

static size_t	get_original_size(void *ptr)
{
	t_header	*header_ptr;
	t_header	*tmp;
	t_meta		*meta_ptr;

	ptr -= sizeof(t_meta);
	header_ptr = *arena();
	tmp = NULL;
	meta_ptr = NULL;
	while (header_ptr)
	{
		tmp = header_ptr + 1;
		meta_ptr = (t_meta *)tmp;
		while (meta_ptr)
		{
			if (meta_ptr == (t_meta *)ptr)
				return (meta_ptr->size);
			meta_ptr = meta_ptr->next;
		}
		header_ptr = header_ptr->next;
	}
	return (0);
}

static void		*new_malloc(void *ptr, size_t const size,
				size_t const original_size)
{
	void		*result;

	result = NULL;
	if ((result = malloc(size)) == NULL)
		return (ptr);
	_memcpy(result, ptr, original_size);
	free(ptr);
	return (result);
}

static void		*increase_block(void *ptr, size_t const size,
				size_t const original_size)
{
	t_meta		*meta_ptr;
	void		*result;

	meta_ptr = NULL;
	result = NULL;
	free(ptr);
	ptr -= sizeof(t_meta);
	meta_ptr = (t_meta *)ptr;
	if (meta_ptr->size > original_size && size <= meta_ptr->size)
	{
		meta_ptr->free = false;
		result = (void *)meta_ptr;
		result += sizeof(t_meta);
		return (result);
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	void		*result;
	size_t		original_size;

	result = NULL;
	original_size = 0;
	size += (MEMORY_ALIGN - (size + sizeof(t_meta)) % MEMORY_ALIGN);
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	original_size = get_original_size(ptr);
	if (original_size == 0)
		return (NULL);
	if (original_size && size > original_size)
		return ((result = increase_block(ptr, size, original_size))) ? result
		: new_malloc(ptr, size, original_size);
	return (ptr);
}
