/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:09:46 by tgrivel           #+#    #+#             */
/*   Updated: 2022/05/10 16:55:12 by ldominiq         ###   ########.fr       */
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
		parse(&cmd1, &line);
		add_history(line);
		if (check_build(&cmd1, envp))
			exec_cmd(&cmd1, envp);
		free_cmd(&cmd1);
		free_str(&line);
	}
}

//	CTRL + C (signal interrupt)
static void	sig_int(int n)
{
	if (n == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// CTRL + \ (signal quit)
static void sig_quit(int n)
{
	if (n == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//	1.	Print a welcome message
//	2.	Start the main loop
int
	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	wel_msg();
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	loop(envp);
	return (0);
}
