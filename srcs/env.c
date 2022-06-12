/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:33:49 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/11 23:42:20 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	print each line of environnement variable
void	env(char **envp)
{
	if (envp == 0)
		return ;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
