/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:21:56 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/28 19:31:51 by ldominiq         ###   ########.fr       */
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

//	get length of the enviromnent variable
char	*get_envlen(char *line, char **envp, int *i, int *len)
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

//	get length of the line if we replace all environment variable
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
			if (get_len_util(&len, line, &i))
				return (-1);
		}
		while (line[i] == '$' && ++i)
			get_envlen(line, envp, &i, &len);
		while (line[i] && line[i] != '\"' && (line[i] != '\'' || !td)
			&& line[i] != '$' && ++i)
			len++;
	}
	if (td == 0)
		return (-1);
	return (len);
}

//	return new line where the environment variable are replaced
// 1. measure lenght for the new allocation.
// 2. replace envp with their value.
char	*line_env(char *line, char **envp)
{
	int		len;
	char	*ret;

	len = get_len(line, envp);
	if (check_len(len, line))
		return (NULL);
	ret = malloc(len + 1);
	if (ret == 0)
		return (0);
	ret[len] = 0;
	line_env_util(line, envp, ret);
	free(line);
	return (ret);
}
