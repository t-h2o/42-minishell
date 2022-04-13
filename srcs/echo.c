/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:19:06 by ldominiq          #+#    #+#             */
/*   Updated: 2022/04/13 14:32:57 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *flag, char *str)
{
	if (flag)
	{
		if (str_cmp(flag, "-n") == 0)
			printf("%s", str);
		else
			printf("%s\n", flag);
	}
}
