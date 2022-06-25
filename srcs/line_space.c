/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:05:56 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/25 16:44:25 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	loop_char(char *line, int *i, int *n, char c)
{
	int	check;

	check = 0;
	if (*i > 0 && line[*i - 1] != ' ')
		++(*n);
	while (line[*i] && line[*i] == c)
	{
		if (line[*i + 1] == 0)
			return (-1);
		++(*n);
		++(*i);
		++check;
		if (check == 3)
			return (-1);
		if (line[*i] && line[*i] != ' ' && line[*i] != c)
			++(*n);
	}
	return (0);
}

// count the number of char of line and add +1 sometime:
// <c   -> +1
// <<c  -> +1
// < c  -> +0
// << c -> +0
static int	count(char *line)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == '<')
			if (loop_char(line, &i, &n, '<'))
				return (-1);
		if (line[i] == '>')
			if (loop_char(line, &i, &n, '>'))
				return (-1);
		++i;
		++n;
	}
	return (n);
}

// put line in ret,
// if >>... -> >> ...
// if >...  -> > ...
static void	put_str(char *ret, char *line)
{
	int	i;
	int	dec;

	i = 0;
	dec = 0;
	while (line[i])
	{
		ret[i + dec] = line[i];
		if (line[i] != '>' && line[i] != '<' && \
			line[i] != ' ' && line[i + 1] && \
			(line[i + 1] == '>' || line[i + 1] == '<'))
			ret[i + ++dec] = ' ';
		if (line[i] == '<' && line[i + 1] && \
			line[i + 1] != '<' && line[i + 1] != ' ')
			ret[i + ++dec] = ' ';
		if (line[i] == '>' && line[i + 1] && \
			line[i + 1] != '>' && line[i + 1] != ' ')
			ret[i + ++dec] = ' ';
		i++;
	}
}

// Add space between > and word
// cat <echo.c -> cat < echo.c
char	*line_space(char *line)
{
	int		n;
	char	*ret;

	n = count(line);
	if (n == -1)
		return (0);
	ret = malloc(n + 1);
	if (ret == 0)
		return (0);
	ret[n] = 0;
	line = trim_space(line);
	put_str(ret, line);
	free(line);
	return (ret);
}
