/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:18:09 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/12 00:32:23 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#define BS_CWD 64

//	get environnement personnal working directory
//	if error range (buffer too small) realloc a bigger buffer and try again
void
	pwd(void)
{
	char			*pwd;
	int				errno ;
	unsigned int	i;

	pwd = malloc(BS_CWD);
	getcwd(pwd, BS_CWD);
	i = 2;
	while (errno == ERANGE)
	{
		free(pwd);
		errno = 0;
		pwd = malloc(BS_CWD * i);
		getcwd(pwd, BS_CWD * i);
		i++;
	}
	printf("%s\n", pwd);
	free(pwd);
}
