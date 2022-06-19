/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:19:06 by ldominiq          #+#    #+#             */
/*   Updated: 2022/06/19 10:40:19 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_nl(char **arg)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
	}
}

void	echo(t_cmd *cmd1)
{
	if (cmd1->arg[1] != NULL)
	{
		if (ft_strcmp(cmd1->arg[1], "-n") != 0)
		{
			print_nl(&(cmd1->arg[1]));
		}
		else
		{
			print_nl(&(cmd1->arg[0]));
			printf("\n");
		}
	}
}
