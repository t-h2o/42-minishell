/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:21:56 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/29 20:13:18 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

// an enviromnent variable [A-Z] or [a-z] or '_'
static int	name_env(char c)
{
	if (c == '_')
		return (1);
	if ('a' <= c && c <= 'z')
		return (1);
	if ('A' <= c && c <= 'Z')
		return (1);
	return (0);
}

// get length of the enviromnent variable
static char	*get_envlen(char *line, char **envp, int *i, int *len)
{
	char	*env;
	char	*var;
	int		start;

	start = *i;
	while (name_env(line[*i]))
	{
		(*i)++;
	}
	var = ft_strndup((line + start), *i - start);
	env = my_getenv(var, envp);
	free(var);
	if (len)
		*len += ft_strlen(env);
	return (env);
}

// get length of the line if we replace all environment variable
static int	get_len(char *line, char **envp)
{
	int		i;
	int		len;
	int		td;

	i = 0;
	len = 0;
	td = 1;
	while (line[i])
	{
		if (line[i] == '\"' && ++i && ++len)
			td = (td + 1) % 2;
		while (td && line[i] == '\'' && ++i)
		{
			len += 2;
			while (line[i] && line[i] != '\'' && ++i)
				len++;
			if (line[i] == 0)
				return (-1);
			i++;
		}
		while (line[i] == '$' && ++i)
			get_envlen(line, envp, &i, &len);
		while (line[i] && line[i] != '\"'
			&& (line[i] != '\'' || !td) && line[i] != '$' && ++i)
			len++;
	}
	if (td == 0)
		return (-1);
	return (len);
}

// return new line where the environment variable are replaced
char	*line_env(char *line, char **envp)
{
	(void)envp;
	int		i;
	int		r;
	int		e;
	int		len;
	char	*env;
	char	*ret;
	int		td;

	len = get_len(line, envp);
	if (len == -1)
		free(line);
	if (len == -1)
		return (0);
	ret = malloc(len + 1);
	if (ret == 0)
		return (0);
	ret[len] = 0;
	i = 0;
	r = 0;
	td = 1;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			ret[r++] = line[i++];
			td = (td + 1) % 2;
		}
		while (line[i] == '\'' && td)
		{
			ret[r++] = line[i++];
			while (line[i] && line[i] != '\'')
				ret[r++] = line[i++];
			ret[r++] = line[i++];
		}
		while (line[i] == '$' && ++i)
		{
			env = get_envlen(line, envp, &i, 0);
			e = 0;
			while (env && env[e])
				ret[r++] = env[e++];
		}
		while (line[i] && (line[i] != '\"' || td)
			&& (line[i] != '\'' || !td) && line[i] != '$')
			ret[r++] = line[i++];
	}
	free(line);
	return (ret);
}
