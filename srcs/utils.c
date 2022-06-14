/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:16:27 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/14 22:31:05 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	if the two string are equal			--> return 1
//	if the two string are not equal		--> return 0
//	if one of the two is null pointe	--> return -1
int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (-1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == 0 && *s2 == 0)
		return (1);
	return (0);
}

char	*str_dup(char *s)
{
	int		len;
	char	*ret;

	if (s == 0)
		return (0);
	len = 0;
	while (s[len])
		len++;
	ret = malloc(len + 1);
	if (ret == 0)
		return (0);
	ret[len] = 0;
	while (len--)
		ret[len] = s[len];
	return (ret);
}

char	*ft_strndup(char *str, int n)
{
	char	*ret;

	ret = malloc(n + 1);
	if (ret == 0)
		return (0);
	ret[n] = 0;
	while (n--)
		ret[n] = str[n];
	return (ret);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}
