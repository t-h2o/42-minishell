/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:30:16 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/25 15:06:25 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	inline int	getpos(const char *str, const char c)
{
	int	pos;

	pos = ft_strchr(str, c) - str;
	if (pos == 0)
		return (ft_strlen((char *)str));
	return (pos);
}

static int	get_index(char *tf, char	**ev)
{
	size_t	i;

	i = -1;
	while (ev[++i])
		if (!ft_strncmp(tf, ev[i], getpos(tf, '=')))
			return (i);
	return (-1);
}

static char	**dup_add_table(char **envp, char *add, int pos)
{
	char	**new_env;
	int		i;

	i = 0;
	while (envp[i])
		++i;
	if (pos == -1)
	{
		if (!dup_add_table_short(&new_env, add, &i, envp))
			return (0);
	}
	else
	{
		if (!dup_table(&new_env, &i, pos, envp))
			return (0);
		add_table(&new_env, add, &i, envp);
	}
	free(envp);
	return (new_env);
}

void	export_pwd(char ***envp, char *newpwd)
{
	int		pos;

	pos = get_index(newpwd, *envp);
	if (pos != -1)
	{
		*envp = dup_add_table(*envp, newpwd, pos);
	}
}

void	export(t_cmd *command, char ***envp)
{
	int		i;
	int		pos;

	if (*envp == 0)
		return ;
	i = 0;
	while (command->arg[++i])
	{
		pos = get_index(command->arg[i], *envp);
		*envp = dup_add_table(*envp, command->arg[i], pos);
	}
}
