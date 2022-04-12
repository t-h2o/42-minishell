/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:09:46 by tgrivel           #+#    #+#             */
/*   Updated: 2022/04/12 02:19:17 by melogr@phy       ###   ########.fr       */
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
	char	*line;
	int		ret;

	while (1)
	{
		line = readline("it's the Prompt $ ");
		if (line == 0)
		{
			printf("\n");
			return ;
		}
		ret = check_build(line, envp);
		if (ret)
			parse(line);
		free(line);
	}
}

//	CTRL + C (signal interrupt)
static void	sig_int(int n)
{
	if (n == SIGINT)
		printf("signal interrupt\n");
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
	loop(envp);
	return (0);
}
