/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:19:06 by ldominiq          #+#    #+#             */
/*   Updated: 2022/04/13 15:40:52 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_cmd *cmd1)
{
	int		i;

	i = 0;
	if (str_cmp(cmd1->arg[++i], "-n") == 0)
	{
		while (cmd1->arg[++i])
			printf("%s ", cmd1->arg[i]);
	}
	else
	{
		i--;
		while (cmd1->arg[++i])
			printf("%s ", cmd1->arg[i]);
		printf("\n");
	}
}
