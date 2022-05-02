/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:55:29 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/05/02 22:17:05 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

// Works but need to press enter to see 'it's the Prompt $ :/'
void	exec_cmd(t_cmd *cmd1)
{
	int	pid;
	if (access(cmd1->cmd, X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execv(cmd1->cmd, cmd1->arg);
			exit(0);
		}
	}
	else
		errmsg("minishell: command not found: ", cmd1->cmd);
}
