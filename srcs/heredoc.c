/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:12:15 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/14 00:35:06 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	if the two string are equal			--> return 1
//	if the two string are not equal		--> return 0
//	if one of the two is null pointe	--> return -1
static int	str_cmp_dh(char *s1, char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == '\n' && *s2 == 0)
		return (1);
	return (0);
}

static void	print_temp(char *line, int fd)
{
	if (line == 0)
		return ;
	while (*line)
	{
		write(fd, line, 1);
		line++;
	}
}

void
	here_doc(char *eof)
{
	char	*line;
	int		fd_hd;

	line = 0;
	fd_hd = open("/tmp/.minishell-here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (str_cmp_dh(line, eof) == 0)
	{
		print_temp(line, fd_hd);
		free_str(&line);
		write(1, ">>> ", 4);
		line = get_next_line(0);
	}
	free_str(&line);
	close(fd_hd);
}
