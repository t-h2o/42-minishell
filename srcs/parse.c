/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:15:18 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/13 23:24:38 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	readline, if the 1st character is '\0', it's just a return line
//	t_cmd->cmd		: path/of/bin/command
//	t_cmd->arg[0]	: cmd
//	t_cmd->arg[1]	: argument_1
//	t_cmd->arg[n]	: argument_n
//	t_cmd->arg[last]: NULL POINTER
char	*parse(t_line *inputs, char *line)
{
	char	**split;

	// what is the use of this check you already verify beforehand whether or not the string is null
	if (line[0] == 0)
		return (0);
	line = line_env(line);
	if (line)
	{
		split = line_sep(line);
		if (split)
			setcmd(inputs, split);
	}
	return (line);
}
