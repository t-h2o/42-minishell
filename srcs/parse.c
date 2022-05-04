/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:15:18 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/05/04 17:40:03 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	readline, if the 1st character is '\0', it's just a return line
//	t_cmd->cmd		: path/of/bin/command
//	t_cmd->arg[0]	: cmd
//	t_cmd->arg[1]	: argument_1
//	t_cmd->arg[n]	: argument_n
//	t_cmd->arg[last]: NULL POINTER
void	parse(t_cmd *cmd1, char **line)
{
	char	**split;

	if (line[0][0] == 0)
		return ;
	*line = line_env(line);
	if (*line)
	{
		split = line_sep(*line);
		if (split)
			setcmd(cmd1, split);
	}
	int	i = -1;
	printf("\nARGUMENTS\n------------\n");
	while (cmd1->arg && cmd1->arg[++i])
		printf("%d | %s\n", i, cmd1->arg[i]);
	printf("------------\n");
}
