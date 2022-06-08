/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:55:29 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/08 00:19:06 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	exec(t_cmd *cmd1, char **envp)
{
	int	pid;

	if (access(cmd1->cmd, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			errmsg("minishell: fork: error", 0);
		if (pid == 0)
		{
			execve(cmd1->cmd, cmd1->arg, envp);
			exit(0);
		}
		waitpid(pid, NULL, 0);
	}
	else
		errmsg("minishell: command not found: ", cmd1->cmd);
}

void   exec_cmd(t_line *inputs, char **envp)
{

   int ret;

   ret = check_build(inputs->cmds, envp);
   if (ret == 1)
   {
       exec(inputs->cmds, envp);
   }
   if (ret == 2)
   {
	   inputs->loop = 0;
   }
}
