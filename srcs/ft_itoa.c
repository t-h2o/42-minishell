/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:47:58 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/24 10:13:35 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int
	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char
	*ft_itoa(int n)
{
	char	*s;
	int		len;
	size_t	nbr;

	len = ft_intlen(n);
	s = malloc(len + 1);
	if (!s)
		return (0);
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		nbr = (size_t) n * -1;
		s[0] = '-';
	}
	else
		nbr = n;
	while (nbr > 0)
	{
		s[--len] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (s);
}
