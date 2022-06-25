/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:00:20 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/25 14:45:34 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// s HOME
// s -> HOME=

static char	*expand_string(char *s)
{
	size_t	len;
	char	*ns;

	len = ft_strlen(s);
	ns = malloc(len + 2);
	if (!ns)
		return (0);
	ft_memcpy(ns, s, len);
	ns[len] = '=';
	ns[len + 1] = 0;
	return (ns);
}

char	*my_getenv(char *s, char **envp)
{
	int		i;
	int		j;
	char	*new_s;

	i = 0;
	new_s = expand_string(s);
	if (!new_s)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(new_s, envp[i], ft_strlen(new_s)) == 0)
			break ;
		++i;
	}
	if (envp[i] == 0)
	{
		free(new_s);
		return (0);
	}
	j = 0;
	while (s[j])
		++j;
	free(new_s);
	return (&(envp[i][j + 1]));
}

int	check_equal(char *env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (env[i] == '=')
			return (1);
	}
	return (0);
}
