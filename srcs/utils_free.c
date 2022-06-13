/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:34:11 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/13 23:34:19 by melogr@phy       ###   ########.fr       */
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

void	free_inputs(t_line *inputs)
{
	free_str(&(inputs->inf.file));
	free_str(&(inputs->ouf.file));
	if (inputs->cmds)
	{
		free_cmds(inputs->cmds);
		free(inputs->cmds);
		inputs->cmds = 0;
	}
}
