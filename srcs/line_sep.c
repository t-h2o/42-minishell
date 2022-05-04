/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:15:03 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/05/04 16:32:10 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	copy up to a whit character
static char	*put_str(char *s, int *i)
{
	char	*ret;
	int		len;
	int		tmp;
	int		td;
	int		jump;

	td = 0;
	len = 0;
	tmp = 0;
	if (s == 0)
		return (0);
	while (s[*i + len] && ((td % 2) || s[*i + len] != ' '))
	{
		if (s[*i + len] == '\"' || s[*i + len] == '\'')
			td++;
		++len;
	}
	ret = malloc(len - td + 1);
	if (ret == 0)
		return (0);
	ret[len - td] = 0;
	tmp = len;
	jump = 0;
	while (len-- - td)
	{
		while (s[*i + len - jump] == '\"' || s[*i + len - jump] == '\'')
			jump++;
		ret[len - td] = s[*i + len - jump];
	}
	*i += tmp;
	return (ret);
}

//	1.	"   "    \0 (double quote space)
//	1.	""       \0 (double quote empty)
//	1.	"""""""  \0 (many empty double quote)
//	0.           \0 (full space)
//	1.  xxxxxxxxx\0 (word without space)
static int	count(char *line)
{
	int	i;
	int	arg;

	i = 0;
	arg = 0;
	while (line[i])
	{
		while (line[i] == '\"' && ++i)
		{
			while (line[i] != '\"')
				i++;
			i++;
		}
		if (line[i] && line[i] != ' ' && line[i] != '\"')
		{
			while (line[i] && line[i] != ' ' && line[i] != '\"')
				i++;
		}
		if (line[i] == ' ')
		{
			 while (line[i] == ' ')
			 	i++;
			arg++;
		}
		else if (line[i] == 0)
			arg++;
	}
	return (arg);
}

//	split the string by characters in sep string
char	**line_sep(char *line)
{
	char	**ret;
	int		arg;
	int		i;

	arg = count(line);
	ret = malloc(sizeof(char *) * (arg + 1));
	if (ret == 0)
		return (0);
	ret[arg] = 0;
	i = 0;
	arg = 0;
	while (ret[arg])
	{
		while (line[i] == ' ')
			i++;
		ret[arg] = put_str(line, &i);
		arg++;
	}
	return (ret);
}
