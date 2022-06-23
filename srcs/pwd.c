/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 23:18:09 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/23 23:47:59 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#define BS_CWD 64

char
	*getpwd(void)
{
	char			*pwd;
	int				errno ;
	unsigned int	i;

	pwd = malloc(BS_CWD);
	if (pwd == 0)
		return (0);
	getcwd(pwd, BS_CWD);
	i = 2;
	while (errno == ERANGE)
	{
		free(pwd);
		errno = 0;
		pwd = malloc(BS_CWD * i);
		if (pwd == 0)
			return (0);
		getcwd(pwd, BS_CWD * i);
		i++;
	}
	return (pwd);
}

//	get environnement personnal working directory
//	if error range (buffer too small) realloc a bigger buffer and try again
void
	pwd(void)
{
	char	*pwd;

	pwd = getpwd();
	printf("%s\n", pwd);
	free(pwd);
}
