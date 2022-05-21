/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:09:46 by tgrivel           #+#    #+#             */
/*   Updated: 2022/05/12 11:16:52 by ldominiq         ###   ########.fr       */
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

//	Infinite loop :
//	readline, if line is null, (CTRL + D)
static void
	loop(char **envp)
{
	t_cmd	cmd1;
	char	*line;

	cmd1.cmd = 0;
	cmd1.arg = 0;
	while (1)
	{
		line = readline("it's the Prompt $ ");
		if (line == 0)
		{
			clear_history();
			printf("exit\n");
			exit(0);
		}
		line = parse(&cmd1, line);
		add_history(line);
		if (check_build(&cmd1, envp))
			exec_cmd(&cmd1, envp);
		free_cmd(&cmd1);
		free_str(&line);
	}
}

//	1.	Print a welcome message
//	2.	Start the main loop
int
	main(int argc, char **argv, char **envp)
{
	struct termios t;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &t);
	wel_msg();
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	loop(envp);
	return (0);
}
