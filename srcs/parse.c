/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:15:18 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/12 02:15:30 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	parse(char *line)
{
	t_cmd	cmd1;
	int		i;

	cmd1.arg = split(line);
	i = 0;
	while (cmd1.arg[i])
	{
		printf("%s not found\n", cmd1.arg[i]);
		i++;
	}
	while (i--)
		free(cmd1.arg[i]);
	free(cmd1.arg);
}
