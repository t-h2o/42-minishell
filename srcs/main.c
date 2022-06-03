/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:09:46 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/03 17:01:56 by tgrivel          ###   ########.fr       */
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
	t_line	inputs;
	char	*line;

	inputs.inf = 0;
	inputs.ouf = 0;
	inputs.cmds = 0;
	while (1)
	{
		line = readline("it's the Prompt $ ");
		if (line == 0)
		{
			clear_history();
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		line = parse(&inputs, line);
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
