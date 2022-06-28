/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:40:23 by ldominiq          #+#    #+#             */
/*   Updated: 2022/06/28 19:36:34 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	get_len_util(int *len, char *line, int *i)
{
	*len += 2;
	while (line[*i] && line[*i] != '\'' && ++(*i))
		(*len)++;
	if (line[*i] == 0)
		return (1);
	(*i)++;
	return (0);
}

static void	copy_line(char *line, int *i, int *r, char *ret)
{
	ret[(*r)++] = line[(*i)++];
	while (line[*i] && line[*i] != '\'')
		ret[(*r)++] = line[(*i)++];
	ret[(*r)++] = line[(*i)++];
}

static void	copy_env(char *env, char *ret, int *r)
{
	int	e;

	e = 0;
	while (env && env[e])
		ret[(*r)++] = env[e++];
}

void	line_env_util(char *line, char **envp, char *ret)
{
	int		td;
	int		r;
	char	*env;
	int		i;

	r = 0;
	i = 0;
	td = 1;
	if (line[i] == '\"')
	{
		ret[r++] = line[i++];
		td = (td + 1) % 2;
	}
	while (line[i] == '\'' && td)
		copy_line(line, &i, &r, ret);
	while (line[i] == '$' && ++i)
	{
		env = get_envlen(line, envp, &i, 0);
		copy_env(env, ret, &r);
	}
	while (line[i] && (line[i] != '\"' || !td)
		&& (line[i] != '\'' || !td) && line[i] != '$')
		ret[r++] = line[i++];
}

int	check_len(int len, char *line)
{
	if (len < 0)
	{
		free(line);
		return (1);
	}
	return (0);
}
