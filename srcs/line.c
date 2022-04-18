/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:15:32 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/18 11:19:00 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	return environment variable value
static char	*env_len(char *s, int *i, int *len)
{
	char	*env;
	char	*var;
	int		j;

	j = 0;
	while (s[j] && s[j] != ' ' && s[j] != '\'')
		j++;
	var = malloc(j + 1);
	var[j] = 0;
	*i += j;
	while (j--)
		var[j] = s[j];
	env = getenv(var);
	j = 0;
	while (env[j])
		j++;
	*len += j;
	free(var);
	return (env);
}

//	count length of the new line
static void	count(char *line, int *i, int *len)
{
	*len = 0;
	*i = 0;
	while (line[*i])
	{
		while (line[*i] == '\'')
		{
			(*i)++;
			(*len)++;
			while (line[*i] != 0 && line[*i] != '\'')
			{
				(*i)++;
				(*len)++;
			}
			(*i)++;
			(*len)++;
		}
		while (line[*i] == '$')
		{
			(*i)++;
			env_len(&(line[*i]), i, len);
		}
		while (line[*i] && line[*i] != '$' && line[*i] != '\'')
		{
			(*i)++;
			(*len)++;
		}
	}
}

//	replace the environment variable in line by its value
char	*put_env_in_line(char *line)
{
	char	*ret;
	char	*env;
	int		len;
	int		i;
	int		j;

	count(line, &i, &len);
	ret = malloc(len + 1);
	ret[len] = 0;
	i = 0;
	len = 0;
	while (line[i])
	{
		while (line[i] == '\'')
		{
			ret[len++] = line[i++];
			while (line[i] != 0 && line[i] != '\'')
				ret[len++] = line[i++];
			ret[len++] = line[i++];
		}
		while (line[i] == '$')
		{
			i++;
			env = env_len(&(line[i]), &i, &j);
			j = 0;
			while (env[j])
				ret[len++] = env[j++];
		}
		while (line[i] && line[i] != '$' && line[i] != '\'')
			ret[len++] = line[i++];
	}
	return (ret);
}
