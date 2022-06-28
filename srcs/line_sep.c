/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_sep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:15:03 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/28 20:39:16 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static char	*copy_str(char *s, t_params *p, int *i)
{
	char	*ret;
	int		jump;

	ret = malloc(p->len - p->td + 1);
	if (ret == 0)
		return (0);
	ret[p->len - p->td] = 0;
	jump = 0;
	while (p->len-- - p->td)
	{
		while (s[*i + p->len - jump] == '\"'
			&& (p->type == 0 || p->type == 2))
		{
			p->type = (p->type + 2) % 4;
			jump++;
		}
		while (s[*i + p->len - jump] == '\''
			&& (p->type == 0 || p->type == 1))
		{
			p->type = (p->type + 1) % 2;
			jump++;
		}
		ret[p->len - p->td] = s[*i + p->len - jump];
	}
	return (ret);
}

//	copy up to a white character
//	if the function meet ' or ", count the white characters
static char	*put_str(char *s, int *i)
{
	t_params	p;
	char		*ret;

	if (s == 0)
		return (0);
	init_params(&p);
	while (s[*i + p.len] && (s[*i + p.len] != ' ' || p.type))
	{
		if (s[*i + p.len] == '\"' && (p.type == 0 || p.type == 2))
		{
			p.td++;
			p.type = (p.type + 2) % 4;
		}
		if (s[*i + p.len] == '\'' && (p.type == 0 || p.type == 1))
		{
			p.td++;
			p.type = (p.type + 1) % 2;
		}
		p.len++;
	}
	p.tmp = p.len;
	ret = copy_str(s, &p, i);
	*i += p.tmp;
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
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if (line[i] == 0 && arg == 0)
				return (-1);
			if (line[i] == 0)
				return (arg);
		}
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
		while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
			i++;
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
