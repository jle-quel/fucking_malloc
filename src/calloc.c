/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 11:00:46 by jle-quel          #+#    #+#             */
/*   Updated: 2018/10/23 11:02:19 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <allocation.h>

void	*calloc(size_t count, size_t eltsize)
{
	size_t const	size = count * eltsize;
	void			*value;

	value = malloc(size);
	if (value != 0)
		_bzero(value, size);
	return (value);
}
