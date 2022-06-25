/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:33:49 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/25 12:41:49 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

// Duplicate the table of environment pointer from the main
char	**dup_envp(char **envp)
{
	char	**ret;
	int		n;

	if (envp == 0)
		return (0);
	n = 0;
	while (envp[n])
		n++;
	ret = malloc((n + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[n] = 0;
	while (n--)
	{
		ret[n] = ft_strdup(envp[n]);
		if (ret[n] == 0)
			return (0);
	}
	return (ret);
}

//	print each line of environnement variable
void	env(char **envp)
{
	if (envp == 0)
		return ;
	while (*envp)
	{
		if (check_equal(*envp))
			printf("%s\n", *envp);
		envp++;
	}
}
