/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:21:56 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/29 20:32:21 by melogr@phy       ###   ########.fr       */
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
// ind[0]: index of line
// ind[1]: index of the return line
// ind[2]: index of environment variable
// ind[3]: toggle double quotes
// ind[4]: lenght of the return string
char	*line_env(char *line, char **envp)
{
	char	*env;
	char	*ret;
	int		ind[4];

	ind[0] = 0;
	ind[1] = 0;
	ind[2] = 0;
	ind[3] = 1;
	ind[4] = get_len(line, envp);
	if (ind[4] == -1)
		free(line);
	if (ind[4] == -1)
		return (0);
	ret = malloc(ind[4] + 1);
	if (ret == 0)
		return (0);
	ret[ind[4]] = 0;
	while (line[ind[0]])
	{
		if (line[ind[0]] == '\"')
		{
			ret[ind[1]++] = line[ind[0]++];
			ind[3] = (ind[3] + 1) % 2;
		}
		while (line[ind[0]] == '\'' && ind[3])
		{
			ret[ind[1]++] = line[ind[0]++];
			while (line[ind[0]] && line[ind[0]] != '\'')
				ret[ind[1]++] = line[ind[0]++];
			ret[ind[1]++] = line[ind[0]++];
		}
		while (line[ind[0]] == '$' && ++ind[0])
		{
			env = get_envlen(line, envp, &ind[0], 0);
			ind[2] = 0;
			while (env && env[ind[2]])
				ret[ind[1]++] = env[ind[2]++];
		}
		while (line[ind[0]] && (line[ind[0]] != '\"' || ind[3])
			&& (line[ind[0]] != '\'' || !ind[3]) && line[ind[0]] != '$')
			ret[ind[1]++] = line[ind[0]++];
	}
	free(line);
	return (ret);
}
