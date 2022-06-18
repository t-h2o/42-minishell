/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:00:20 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/18 18:24:23 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char *s, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(s, envp[i], ft_strlen(s)))
			break ;
		++i;
	}
	j = 0;
	while (s[j])
		++j;
	return (&(envp[i][j + 1]));
}
