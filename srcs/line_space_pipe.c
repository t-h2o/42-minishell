/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_space_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:52:12 by lgyger            #+#    #+#             */
/*   Updated: 2022/06/25 16:55:38 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

char	*trim_space(char *line)
{
	int		i;
	int		pos;
	char	*str;

	pos = strchr(line, '|') - line;
	if (pos < 0)
		return (line);
	str = malloc(strlen(line) + 3);
	i = -1;
	while (++i != pos)
		str[i] = line[i];
	str[i++] = ' ';
	str[i++] = '|';
	str[i] = ' ';
	while (line[++pos])
		str[++i] = line[pos];
	str[i + 1] = 0;
	line = str;
	return (line);
}
