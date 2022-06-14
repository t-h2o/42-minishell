/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:19:06 by ldominiq          #+#    #+#             */
/*   Updated: 2022/06/07 16:04:02 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_cmd *cmd1)
{
	int		i;

	i = 0;
	if (cmd1->arg[1] != NULL)
	{
		if (ft_strcmp(cmd1->arg[++i], "-n") != 0)
		{
			while (cmd1->arg[++i])
			{
				printf("%s", cmd1->arg[i]);
				if (cmd1->arg[i + 1])
					printf(" ");
			}
		}
		else
		{
			i--;
			while (cmd1->arg[++i])
			{
				printf("%s", cmd1->arg[i]);
				if (cmd1->arg[i + 1])
					printf(" ");
			}
			printf("\n");
		}
	}
}
