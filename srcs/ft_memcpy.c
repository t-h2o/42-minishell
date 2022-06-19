/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:29:22 by lgyger            #+#    #+#             */
/*   Updated: 2022/06/18 20:40:10 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst2;
	const unsigned char	*src2;
	size_t				i;

	dst2 = (unsigned char *) dst;
	src2 = (unsigned char *) src;
	if (dst == NULL && src == NULL && n >= 0)
		return (dst);
	i = 0;
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}
