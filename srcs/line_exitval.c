/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_exitval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:21:56 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/24 15:02:44 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	count(char *line, int ev_len)
{
	int	ret;

	ret = 0;
	while (*line)
	{
		if (*line == '$' && *(line + 1) == '?')
		{
			line += 2;
			ret += ev_len;
		}
		else
		{
			++line;
			++ret;
		}
	}
	return (ret);
}

static void	replace(char *ret, char *line, char *ev_str)
{
	int	i;

	while (*line)
	{
		if (*line == '$' && *(line + 1) == '?')
		{
			line += 2;
			i = 0;
			while (ev_str[i])
			{
				*ret = ev_str[i];
				++ret;
				++i;
			}
		}
		else
		{
			*ret = *line;
			++ret;
			++line;
		}
	}
}

// ev - exit value
char	*line_exitval(char *line)
{
	int		ret_len;
	int		ev_len;
	char	*ev_str;
	char	*ret;

	ev_str = ft_itoa(exit_value);
	ev_len = ft_strlen(ev_str);
	ret_len = count(line, ev_len);
	ret = malloc(ret_len + 1);
	ret[ret_len] = 0;
	replace(ret, line, ev_str);
	free(line);
	return (ret);
}
