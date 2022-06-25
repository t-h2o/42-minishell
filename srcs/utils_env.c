/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:00:20 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/25 14:27:45 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char *s, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(s, envp[i], ft_strlen(s)) == 0)
			break ;
		++i;
	}
	if (envp[i] == 0)
		return (0);
	j = 0;
	while (s[j])
		++j;
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
