/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:58:43 by lgyger            #+#    #+#             */
/*   Updated: 2022/06/20 21:19:31 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	inline int	getpos(const char *str, const char c)
{
	return (ft_strchr(str, c) - str);
}

static int	get_index(char *tf, char	**ev)
{
	size_t	i;

	i = -1;
	while (ev[++i])
		if (!ft_strncmp(tf, ev[i], ft_strlen(tf))
			&& getpos(ev[i], '=') == ft_strlen(tf))
			return (i);
	return (-1);
}

size_t	nbr_bytes( char **ev, const int pos)
{
	size_t	ret;
	int		i;

	i = -1;
	ret = 0;
	while (++i != pos && ev[i])
		ret += sizeof(ev[i]);
	return (ret);
}

char	**crt_nenv(char **ev, const size_t pos)
{
	size_t	len;
	char	**new_env;

	len = 0;
	while (ev[len])
		++len;
	new_env = malloc(sizeof(char *) * len + 1);
	new_env[len] = NULL;
	ft_memcpy(new_env, ev, nbr_bytes(ev, pos + 1));
	ft_memcpy(new_env + pos, ev + pos + 1, nbr_bytes(ev + pos, pos));
	free(ev);
	free(*(ev + pos));
	return (new_env);
}

void	unset(t_cmd *command, char ***envp)
{
	int		i;
	int		pos;
	if (!envp[0])
		return ;
	i = 0;
	while (command->arg[++i])
	{
		pos = get_index(command->arg[i], *envp);
		if (pos != -1)
			*envp = crt_nenv(*envp, pos);
	}
}
