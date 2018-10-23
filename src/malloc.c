/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:59:01 by jle-quel          #+#    #+#             */
/*   Updated: 2018/10/23 11:00:36 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allocation.h>

static inline uint8_t	get_allocation_type(size_t const size)
{
	if (size <= TINY_MAX)
		return (TINY);
	else if (size <= SMALL_MAX)
		return (SMALL);
	else
		return (LARGE);
}

void					*malloc(size_t size)
{
	uint8_t const	allocation_type = get_allocation_type(size);
	void			*ptr;

	ptr = NULL;
	if (size == 0)
		size = 1;
	size += (MEMORY_ALIGN - (size + sizeof(t_meta)) % MEMORY_ALIGN);
	if ((ptr = search_page(allocation_type, size)))
		return (ptr + sizeof(t_meta));
	if ((ptr = new_page(allocation_type, size)))
		return (ptr + sizeof(t_meta));
	return (NULL);
}
