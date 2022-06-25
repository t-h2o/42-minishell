/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_space_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:52:12 by lgyger            #+#    #+#             */
/*   Updated: 2022/06/25 20:50:57 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>


static	int	get_size(char *line)
{
	char	*buf;
	int		i;
	
	i = 0;
	buf = strchr(line, '|');
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
		if (line[pos] == '|')
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


