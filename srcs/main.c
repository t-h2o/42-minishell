/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:09:46 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/25 20:41:54 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	display a welcome message
static void
	wel_msg(void)
{
	printf("\n\t###############################\n");
	printf("\t#                             #\n");
	printf("\t#  MiniShell by Lucas & Theo  #\n");
	printf("\t#                             #\n");
	printf("\t###############################\n\n");
}

static void	setinputs(t_line *inputs)
{
	inputs->inf.file = 0;
	inputs->inf.eof = 0;
	inputs->ouf.file = 0;
	inputs->inf.flag = 0;
	inputs->ouf.flag = 0;
	inputs->cmds = 0;
	inputs->loop = 1;
}

//	Infinite loop :
//	readline, if line is null, (CTRL + D)
static void
	loop(char ***envp)
{
	t_line	inputs;
	char	*line;

	setinputs(&inputs);
	while (inputs.loop)
	{
		line = readline("it's the Prompt $ ");
		if (line == 0)
		{
			clear_history();
			printf("exit\n");
			inputs.loop = 0;
			break ;
		}
		add_history(line);
		line = parse(&inputs, line, *envp);
		if (line)
			exec_cmd(&inputs, envp);
		free_inputs(&inputs);
		free_str(&line);
	}
}

//	1.	Print a welcome message
//	2.	Start the main loop
int
	main(int argc, char **argv, char **envp)
{
	struct termios	save;
	struct termios	curr;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &curr);
	tcgetattr(STDIN_FILENO, &save);
	curr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &curr);
	wel_msg();
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	envp = dup_envp(envp);
	if (envp)
		loop(&envp);
	free_tab(&envp);
	tcsetattr(STDIN_FILENO, 0, &save);
	return (0);
}
