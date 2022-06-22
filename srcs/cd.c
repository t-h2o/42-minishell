/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:01:54 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/22 19:58:06 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_cmd *command, char **envp)
{
	char	*home;

	if (command->arg[1])
		chdir(command->arg[1]);
	else
	{
		home = my_getenv("HOME", envp);
		chdir(home);
	}
}
