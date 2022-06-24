/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:55:29 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/24 09:53:19 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

#define STDIN 0
#define STDOUT 1

#define PIPE_WRITE 1
#define PIPE_READ 0

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

static void	subprocess(t_cmd *command, char **envp, int fd_inf_ouf[2], int *ret)
{
	pid_t	child;
	int		fd[2];

	if (command->next != NULL)
		pipe(fd);
	child = fork();
	if (child == -1)
		printf("child ERROR\n");
	else if (child == 0)
	{
		dup2(fd_inf_ouf[0], STDIN);
		if (command->next != NULL)
			dup2(fd[PIPE_WRITE], STDOUT);
		else
			dup2(fd_inf_ouf[1], STDOUT);
		close(fd[PIPE_READ]);
		execution(command, envp, ret);
	}
	else
	{
		waitpid(child, ret, 0);
		*ret = WEXITSTATUS(*ret);
		close(fd[PIPE_WRITE]);
		fd_inf_ouf[0] = fd[PIPE_READ];
	}
}

static void	open_infile(t_file inf, t_file ouf, int fd_inf_ouf[2])
{
	int	fd;

	if (inf.file != 0)
	{
		fd = open(inf.file, inf.flag);
		if (fd == -1)
			fd_inf_ouf[0] = STDIN;
		else
			fd_inf_ouf[0] = fd;
	}
	if (ouf.file != 0)
	{
		fd = open(ouf.file, ouf.flag, 0644);
		if (fd == -1)
			fd_inf_ouf[1] = STDOUT;
		else
			fd_inf_ouf[1] = fd;
	}
}

void	exec_cmd(t_line *inputs, char ***envp)
{
	t_cmd	*commands;
	int		fd_inf_ouf[2];

	open_infile(inputs->inf, inputs->ouf, fd_inf_ouf);
	commands = inputs->cmds;
	while (commands != NULL)
	{
		if (ft_strcmp(commands->arg[0], "export") && commands->arg[1] != 0)
			export(commands, envp);
		else if (ft_strcmp(commands->arg[0], "cd"))
			cd(commands, envp);
		else if (ft_strcmp(commands->arg[0], "unset"))
			unset(commands, envp);
		else if (ft_strcmp(commands->arg[0], "exit") && commands->next == 0)
			inputs->loop = 0;
		else
			subprocess(commands, *envp, fd_inf_ouf, &exit_value);
		commands = commands->next;
	}
	if (fd_inf_ouf[1] != 1)
		close(fd_inf_ouf[1]);
}
