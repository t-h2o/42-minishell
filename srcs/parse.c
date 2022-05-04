/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 01:15:18 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/05/04 16:18:24 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	append = path + '/' + cmd
static char	*append(char *s1, char *s2)
{
	char	*app;
	int		len;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	i = 0;
	while (s2[i])
		i++;
	len += i + 1;
	app = malloc(len + 1);
	if (app == 0)
		return (0);
	app[len] = 0;
	len = 0;
	i = 0;
	while (s1[i])
		app[len++] = s1[i++];
	app[len++] = '/';
	i = 0;
	while (s2[i])
		app[len++] = s2[i++];
	return (app);
}

//	get the path environnement variable,
//	test each path to check which path is the good one
//	PATH=path/bin1:path/bin2
//	we need split PATH by ':'
static void	getpath(t_cmd *cmd1)
{
	int		i;
	char	*pcmd;
	char	*path;
	char	**pathall;

	path = getenv("PATH");
	pathall = split(path, ":");
	if (pathall == 0)
		return ;
	i = 0;
	while (pathall[i])
	{
		pcmd = append(pathall[i++], cmd1->cmd);
		if (access(pcmd, X_OK) == 0)
		{
			free_str(&cmd1->cmd);
			cmd1->cmd = pcmd;
			break ;
		}
		free_str(&pcmd);
	}
	free_tab(&pathall);
}

//	readline, if the 1st character is '\0', it's just a return line
//	t_cmd->cmd		: path/of/bin/command
//	t_cmd->arg[0]	: cmd
//	t_cmd->arg[1]	: argument_1
//	t_cmd->arg[n]	: argument_n
//	t_cmd->arg[last]: NULL POINTER
void	parse(t_cmd *cmd1, char **line)
{
	if (line[0][0] == 0)
		return ;
	*line = line_env(line);
	if (*line)
		cmd1->arg = line_sep(*line);
	if (cmd1->arg)
	{
		cmd1->cmd = str_dup(cmd1->arg[0]);
		getpath(cmd1);
	}
	int	i = -1;
	printf("\nARGUMENTS\n------------\n");
	while (cmd1->arg && cmd1->arg[++i])
		printf("%d | %s\n", i, cmd1->arg[i]);
	printf("------------\n");
}
