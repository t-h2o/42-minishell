/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:09:46 by tgrivel           #+#    #+#             */
/*   Updated: 2022/04/08 17:27:55 by theo             ###   ########.fr       */
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
void
	loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("it's the Prompt $ ");
		if (line == 0)
			return (0);
		check_build(line);
		free(line);
	}
}

//	1.	Print a welcome message
//	2.	Start the main loop
int
	main(void)
{
	wel_msg();
	loop();
}
