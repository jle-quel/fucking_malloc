/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:48:38 by jle-quel          #+#    #+#             */
/*   Updated: 2018/10/23 10:49:28 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allocation.h>

t_header	**arena(void)
{
	static t_header	*ptr;

	return (&ptr);
}

void		create_header(const uint8_t allocation_type, const size_t page_size,
			void *ptr)
{
	t_header	*header_ptr;

	header_ptr = (t_header *)ptr;
	header_ptr->type = allocation_type;
	header_ptr->page_size = page_size;
	header_ptr->next = NULL;
	header_ptr->opti = NULL;
}

void		create_meta(const uint8_t status, const size_t size,
			void *ptr, void *next)
{
	t_meta	*meta_ptr;

	meta_ptr = (t_meta *)ptr;
	meta_ptr->free = status;
	meta_ptr->size = size;
	meta_ptr->next = next;
}
