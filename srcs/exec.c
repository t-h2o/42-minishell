/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:55:29 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/12 11:20:16 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

#define STDIN 0
#define STDOUT 1

static void	execution(t_cmd *command, char **envp, int *ret)
{
	*ret = check_build(command, envp);
	if (*ret == 1)
	{
		if (access(command->cmd, X_OK) == 0)
			execve(command->cmd, command->arg, envp);
		else
			errmsg("minishell: command not found: ", command->cmd);
	}
	if (*ret == 2)
		exit(42);
	else
		exit(1);
}

static void	subprocess(t_cmd *command, char **envp, int *fdinf, int *ret)
{
	pid_t	child;
	int		fd[2];

	pipe(fd);
	child = fork();
	if (child == -1)
		printf("child ERROR\n");
	else if (child == 0)
	{
		dup2(*fdinf, STDIN);
		if (command->next != NULL)
			dup2(fd[1], STDOUT);
		close(fd[0]);
		execution(command, envp, ret);
	}
	else
	{
		waitpid(child, ret, 0);
		*ret = WEXITSTATUS(*ret);
		close(fd[1]);
		*fdinf = fd[0];
	}
}

static int	open_infile(t_file inf)
{
	int	fd;

	if (inf.file == 0)
		return (0);
	fd = open(inf.file, inf.flag);
	if (fd == -1)
		return (0);
	return (fd);
}

void	exec_cmd(t_line *inputs, char **envp)
{
	t_cmd	*commands;
	int		ret;
	int		fdinf;

	fdinf = open_infile(inputs->inf);
	commands = inputs->cmds;
	while (commands != NULL)
	{
		subprocess(commands, envp, &fdinf, &ret);
		commands = commands->next;
	}
	if (ret == 42)
		inputs->loop = 0;
}
