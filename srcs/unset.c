/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:58:43 by lgyger            #+#    #+#             */
/*   Updated: 2022/06/18 20:22:44 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
static	size_t	getpos(const char *str, const char c)
{
	return strchr(str, c) - str;
}
static int	get_index(char *tf, char  **ev)
{
	size_t	i;

	i = 0;
	while (ev[i])
	{
		if (!strncmp(tf, ev[i], strlen(tf)) && getpos(ev[i], '=') == strlen(tf))
			return i;
		++i;
	}
	return -1;
}
size_t	nbr_bytes( char **ev, const int pos)
{
	size_t	ret;
	int	i;

	i = 0;
	ret = 0;
	while (i != pos && ev[i])
	{
		ret += sizeof(ev[i]);
		++i;
	}
	return ret;
}

char **crt_nenv(char **ev, const size_t pos)
{
	size_t	len;
	char	**new_env;
	len = 0;
	while (ev[len])
		++len;
	new_env = malloc(sizeof(char *) * len);
	new_env[len - 1] = NULL;
	memcpy(new_env, ev, nbr_bytes(ev, pos));
	memcpy(new_env + pos, ev + pos + 1, nbr_bytes(ev + pos + 1, -1));
	return new_env;
}


void	unset(t_cmd *command, char ***envp)
{
	int 	i = 1;
	int 	pos;
	char	**new_env;
	if (!envp[0])
		return ;
	while (command->arg[i])
	{
		pos = get_index(command->arg[i], *envp);
		if (pos != -1)
		{
			new_env = crt_nenv(*envp, pos);
			*envp = new_env;
		}
		++i;
	}
}
