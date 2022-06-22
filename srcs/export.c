/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:30:16 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/22 22:44:28 by melogr@phy       ###   ########.fr       */
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
		new_env = malloc((i + 1 + 1) * sizeof(char *));
		if (new_env == 0)
			return (0);
		new_env[i + 1] = 0;
		new_env[i] = str_dup(add);
		if (new_env[i] == 0)
			return (0);
		while (i-- > 0)
			new_env[i] = envp[i];
	}
	else
	{
		new_env = malloc((i + 1) * sizeof(char *));
		if (new_env == 0)
			return (0);
		new_env[i] = 0;
		while (i-- > (pos + 1))
			new_env[i] = envp[i];
		free(envp[i]);
		new_env[i] = str_dup(add);
		while (i-- > 0)
			new_env[i] = envp[i];
	}
	free(envp);
	return (new_env);
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
