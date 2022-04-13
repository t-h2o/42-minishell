/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:55:29 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/13 10:23:31 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	exec_cmd(t_cmd *cmd1)
{
	if (access(cmd1->cmd, X_OK) == 0)
		printf("%s\n", cmd1->cmd);
	else
		errmsg("minishell: command not found: ", cmd1->cmd);
}
