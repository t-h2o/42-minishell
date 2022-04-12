/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:15:18 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/12 02:37:10 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	parse(t_cmd *cmd1, char *line)
{
	cmd1->arg = split(line);
	cmd1->cmd = str_dup(cmd1->arg[0]);
}