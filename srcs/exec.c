/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:55:29 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/05/07 12:22:20 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	exec_cmd(t_cmd *cmd1, char **envp)
{
	int	pid;

	if (access(cmd1->cmd, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			errmsg("minishell: fork: error");
		if (pid == 0)
		{
			execve(cmd1->cmd, cmd1->arg, envp);
			exit(0);
		}
	}
	else
		errmsg("minishell: command not found: ", cmd1->cmd);
	waitpid(pid, NULL, 0);
}
