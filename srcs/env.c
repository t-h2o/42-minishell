/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:33:49 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/13 23:09:29 by melogr@phy       ###   ########.fr       */
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
	ret[n] = 0;
	while (n--)
		ret[n] = str_dup(envp[n]);
	return (ret);
}

//	print each line of environnement variable
void	env(char **envp)
{
	if (envp == 0)
		return ;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
