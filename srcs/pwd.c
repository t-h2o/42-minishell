/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:18:09 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/22 22:02:29 by ldominiq         ###   ########.fr       */
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
	if (pwd)
	{
		getcwd(pwd, BS_CWD);
		i = 2;
		while (errno == ERANGE)
		{
			free(pwd);
			errno = 0;
			pwd = malloc(BS_CWD * i);
			if (!pwd)
				break ;
			getcwd(pwd, BS_CWD * i);
			i++;
		}
		printf("%s\n", pwd);
		free(pwd);
	}
}
