/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:30:02 by theo              #+#    #+#             */
/*   Updated: 2022/06/03 15:17:10 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	if the two string are equal			--> return 0
//	if the two string are not equal		--> return 1
//	if one of the two is null pointe	--> return -1
int	str_cmp(char *s1, char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (-1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == 0 && *s2 == 0)
		return (0);
	return (1);
}

//	if line is a build command --> return 0
//	if line is not a build command --> return 1
int	check_build(t_cmd *cmd1, char **envp)
{
	if (cmd1->arg == 0)
		return (0);
	if (!str_cmp(cmd1->arg[0], "exit"))
	{
		return(2);
	}
	if (!str_cmp(cmd1->arg[0], "pwd"))
	{
		pwd();
		return (0);
	}
	if (!str_cmp(cmd1->arg[0], "env"))
	{
		env(envp);
		return (0);
	}
	if (!str_cmp(cmd1->arg[0], "echo"))
	{
		echo(cmd1);
		return (0);
	}
	return (1);
}
