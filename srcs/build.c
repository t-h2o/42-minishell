/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:30:02 by theo              #+#    #+#             */
/*   Updated: 2022/06/14 22:31:08 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	if line is a build command --> return 0
//	if line is not a build command --> return 1
int	check_build(t_cmd *cmd1, char **envp)
{
	if (cmd1->arg == 0)
		return (0);
	if (ft_strcmp(cmd1->arg[0], "exit"))
	{
		return (2);
	}
	if (ft_strcmp(cmd1->arg[0], "pwd"))
	{
		pwd();
		return (0);
	}
	if (ft_strcmp(cmd1->arg[0], "env"))
	{
		env(envp);
		return (0);
	}
	if (ft_strcmp(cmd1->arg[0], "echo"))
	{
		echo(cmd1);
		return (0);
	}
	return (1);
}
