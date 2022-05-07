/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:15:03 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/05/07 13:50:35 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	copy up to a white character
//	if the function meet ' or ", count the white characters
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
	int	type = 0;
	if (s == 0)
		return (0);
	while (s[*i + len] && (s[*i + len] != ' ' || type))
	{
		if (s[*i + len] == '\"' && (type == 0 || type == 2))
		{
			td++;
			type = (type + 2) % 4;
		}
		if (s[*i + len] == '\'' && (type == 0 || type == 1))
		{
			td++;
			type = (type + 1) % 2;
		}
		len++;
	}
	ret = malloc(len - td + 1);
	if (ret == 0)
		return (0);
	ret[len - td] = 0;
	tmp = len;
	jump = 0;
	while (len-- - td)
	{
		while (s[*i + len - jump] == '\"' && (type == 0 || type == 2))
		{
			type = (type + 2) % 4;
			jump++;
		}
		while (s[*i + len - jump] == '\'' && (type == 0 || type == 1))
		{
			type = (type + 1) % 2;
			jump++;
		}
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
		while (line[i] == '\'' && ++i)
		{
			while (line[i] != '\'')
				i++;
			i++;
		}
		while (line[i] == '\"' && ++i)
		{
			while (line[i] != '\"')
				i++;
			i++;
		}
		if (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
		{
			while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
				i++;
		}
		if (line[i] == ' ')
		{
			 while (line[i] == ' ')
			 	i++;
			 if (line[i] == 0 && arg == 0)
				 return (-1);
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

	printf("\nline: %s\n", line);
	arg = count(line);
	if (arg == -1)
		return (0);
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
