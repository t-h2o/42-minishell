/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brexit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:19:32 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/12 23:27:30 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	errmsg(char *msg, char *cmd)
{
	if (msg == 0)
		return ;
	while (*msg)
	{
		write(1, msg, 1);
		msg++;
	}
	while (*cmd)
	{
		write(1, cmd, 1);
		cmd++;
	}
	write(1, "\n", 1);
}
