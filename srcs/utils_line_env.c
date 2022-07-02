/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:23:24 by ldominiq          #+#    #+#             */
/*   Updated: 2022/07/02 11:51:26 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// get length of the enviromnent variable
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

// ind[0]: index of line
// ind[1]: toggle double quote
// ind[2]: length of the environment variable
static inline void	init_index_get_len(int ind[3])
{
	ind[0] = 0;
	ind[1] = 1;
	ind[2] = 0;
}

// spaul
static inline void	dollars(int ind[3], char *line, char **envp)
{
	if (name_env(line[ind[0] + 1]))
		get_envlen(line, envp, &(ind[0]), &(ind[2]));
	else
		++ind[2];
}

// get length of the line if we replace all environment variable
int	get_len(char *line, char **envp)
{
	int	ind[3];

	init_index_get_len(ind);
	while (line[ind[0]])
	{
		if (line[ind[0]] == '\"' && ++ind[0] && ++ind[2])
			ind[1] = (ind[1] + 1) % 2;
		while (ind[1] && line[ind[0]] == '\'' && ++ind[0])
		{
			ind[2] += 2;
			while (line[ind[0]] && line[ind[0]] != '\'' && ++ind[0])
				ind[2]++;
			if (line[ind[0]] == 0)
				return (-1);
			ind[0]++;
		}
		while (line[ind[0]] == '$' && ++ind[0])
			dollars(ind, line, envp);
		while (line[ind[0]] && line[ind[0]] != '\"' && (line[ind[0]] != '\''
				|| !ind[1]) && line[ind[0]] != '$' && ++ind[0])
			ind[2]++;
	}
	if (ind[1] == 0)
		return (-1);
	return (ind[2]);
}
