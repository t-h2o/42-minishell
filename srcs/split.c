/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:15:03 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/12 22:48:35 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	blank characters --> return 1
//	not blank characters --> return 0
static int	blank(char n, char *s)
{
	while (*s)
	{
		if (n == *s)
			return (1);
		s++;
	}
	return (0);
}

//	copy up to a whit character
static char	*put_str(char *s, int *i, char *sep)
{
	char	*ret;
	int		len;
	int		tmp;

	len = 0;
	if (s == 0)
		return (0);
	while (s[*i + len] != 0 && !blank(s[*i + len], sep))
	{
		len++;
	}
	ret = malloc(len + 1);
	if (ret == 0)
		return (0);
	ret[len] = 0;
	tmp = len;
	while (len--)
		ret[len] = s[*i + len];
	*i += tmp;
	return (ret);
}

static int	count(char *line, char *sep)
{
	int	i;
	int	arg;

	i = 0;
	arg = 0;
	while (1)
	{
		while (line[i] && blank(line[i], sep))
			i++;
		if (line[i] == 0)
			break ;
		arg++;
		while (line[i] && !blank(line[i], sep))
			i++;
		if (line[i] == 0)
			break ;
	}
	return (arg);
}

//	split the string by characters in sep string
char	**split(char *line, char *sep)
{
	char	**ret;
	int		arg;
	int		i;

	arg = count(line, sep);
	ret = malloc(sizeof(char *) * (arg + 1));
	if (ret == 0)
		return (0);
	ret[arg] = 0;
	i = 0;
	arg = 0;
	while (1)
	{
		while (line[i] && blank(line[i], sep))
			i++;
		if (line[i] == 0)
			break ;
		ret[arg] = put_str(line, &i, sep);
		arg++;
		if (line[i] == 0)
			break ;
	}
	return (ret);
}
