/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:16:18 by ldominiq          #+#    #+#             */
/*   Updated: 2022/05/12 11:18:18 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	CTRL + C (signal interrupt)
void	sig_int(int n)
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
void	sig_quit(int n)
{
	if (n == SIGQUIT)
		rl_redisplay();
}
