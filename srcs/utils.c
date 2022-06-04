/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:16:27 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/04 10:52:19 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	free the string pointer
//	set the pointer at null, we are protect of double free
void	free_str(char **s)
{
	if (*s == 0)
		return ;
	free(*s);
	*s = 0;
}

void	free_tab(char ***tab)
{
	int	i;

	if (*tab == 0)
		return ;
	i = 0;
	while (tab[0][i])
		++i;
	while (i--)
		free_str(&(tab[0][i]));
	free(*tab);
	*tab = 0;
}

static void	free_cmds(t_cmd *command)
{
	if (command->next)
	{
		free_cmds(command->next);
		free(command->next);
	}
	free(command->cmd);
	free_tab(&(command->arg));
}

void free_inputs(t_line *inputs)
{
	free_str(&(inputs->inf));
	free_str(&(inputs->ouf));
	if (inputs->cmds)
	{
		free_cmds(inputs->cmds);
		free(inputs->cmds);
		inputs->cmds = 0;
	}
}

char	*str_dup(char *s)
{
	int		len;
	char	*ret;

	if (s == 0)
		return (0);
	len = 0;
	while (s[len])
		len++;
	ret = malloc(len + 1);
	if (ret == 0)
		return (0);
	ret[len] = 0;
	while (len--)
		ret[len] = s[len];
	return (ret);
}

char	*ft_strndup(char *str, int n)
{
	char	*ret;

	ret = malloc(n + 1);
	if (ret == 0)
		return (0);
	ret[n] = 0;
	while (n--)
		ret[n] = str[n];
	return (ret);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}
