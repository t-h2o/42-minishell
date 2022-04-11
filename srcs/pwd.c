/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:18:09 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/11 23:23:09 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	get environnement personnal working directory
void
	pwd(void)
{
	char	*env;

	env = getenv("PWD");
	printf("%s\n", env);
}
