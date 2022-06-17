/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:45:19 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/13 23:45:43 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static ssize_t
	gnl_skip(char *s, char c)
{
	ssize_t	n;

	if (!s)
		return (0);
	n = 0;
	while (s[n] && s[n] != c)
		n++;
	return (n);
}
/*	It's like a strlen
 *	but you can choose a char
 *	very good for know where is \n
 */

static char
	*gnl_strsub(char *s)
{
	char	*r;
	ssize_t	n;

	n = gnl_skip(s, '\n') + 1;
	r = (char *)malloc(n + 1);
	if (!r)
		return (0);
	r[n] = 0;
	while (n--)
		r[n] = s[n];
	free(s);
	return (r);
}
/* He delete whats is after the line
 */

static char
	*gnl_decal(char *s)
{
	ssize_t	i;
	ssize_t	n;

	i = 0;
	n = gnl_skip(s, '\n');
	while (i <= BUFFER_SIZE - n)
	{
		s[i] = s[i + n + 1];
		i++;
	}
	while (i <= BUFFER_SIZE + 1)
		s[i++] = 0;
	return (0);
}
/*		BS	= 5 (buff = 6)
 *
 *		in	:	xNabc0	
 *		out	:	abc000
 *
 *		in	:	abcNx0	
 *		out	:	x00000
 *
 *		in	:	abcde0	
 *		out	:	000000
 */

static char
	*gnl_strjoin(char *s1, char *s2)
{
	ssize_t	len;
	ssize_t	i;
	char	*r;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	r = (char *)malloc(gnl_skip(s1, '\0') + gnl_skip(s2, '\0') + 1);
	if (!r)
		return (0);
	r[gnl_skip(s1, '\0') + gnl_skip(s2, '\0')] = 0;
	i = 0;
	len = 0;
	while (s1[i])
		r[len++] = s1[i++];
	i = 0;
	while (s2[i])
		r[len++] = s2[i++];
	free(s1);
	gnl_decal(s2);
	return (r);
}	
/*	The function join s1 and s2 and then
 *	He will free s1 (line)
 *	and decal the s2 (buff)
 */

char
	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || (read(fd, 0, 0) != 0))
		return (0);
	line = 0;
	while (1)
	{
		if (buff[0] == 0)
		{
			if (!(read(fd, buff, BUFFER_SIZE)))
			{
				if (!line)
					return (0);
				else
					return (line);
			}
		}
		line = gnl_strjoin(line, buff);
		if (!line)
			return (0);
		if (line[gnl_skip(line, '\n')] == '\n')
			return (gnl_strsub(line));
	}	
}
