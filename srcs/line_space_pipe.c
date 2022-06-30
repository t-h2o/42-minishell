/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_space_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:52:12 by lgyger            #+#    #+#             */
/*   Updated: 2022/06/30 15:34:42 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	can_i_touch(char *line, char *pos)
{
	char	*first;
	char	*last;

	first = strchr(line, '\"');
	if (first)
	{
		last = strchr(first + 1, '\"');
		if (pos > first && pos < last)
			return (0);
	}
	first = strchr(line, '\'');
	if (first)
	{
		last = strchr(first + 1, '\'');
		if (pos > first && pos < last)
			return (0);
	}
	return (1);
}

static	int	get_size(char *line)
{
	char	*buf;
	int		i;

	i = 0;
	buf = strchr(line, '|');
	if (!buf)
		return (0);
	if ((*(buf - 1) == '\'' && *(buf + 1) == '\'')
		|| (*(buf - 1) == '\"' && *(buf + 1) == '\"'))
		return (0);
	while (buf)
	{
		buf = strchr(buf + 1, '|');
		i += 2;
	}
	return (i);
}

char	*trim_space(char *line)
{
	int		i;
	int		pos;
	char	*str;

	i = get_size(line);
	if (i == 0)
		return (line);
	str = malloc(strlen(line) + i + 1);
	i = -1;
	pos = -1;
	while (line[++pos] && ++i >= 0)
	{
		if (line[pos] == '|' && can_i_touch(line, &line[pos]) == 1)
		{
			str[i++] = ' ';
			str[i++] = '|';
			str[i++] = ' ';
			++pos;
		}
		str[i] = line[pos];
	}
	str[++i] = 0;
	free(line);
	line = str;
	return (line);
}
