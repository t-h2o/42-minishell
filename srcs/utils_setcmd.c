/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_setcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 19:36:46 by ldominiq          #+#    #+#             */
/*   Updated: 2022/06/29 19:42:08 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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
static void	getpath(t_cmd *cmd1, char **envp)
{
	int		i;
	char	*pcmd;
	char	*path;
	char	**pathall;

	path = my_getenv("PATH", envp);
	if (path == 0)
		return ;
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

void	dup_cmd(char **split, char **envp, int *n, t_cmd *ptr)
{
	if (split[*n] && ptr->cmd == 0)
	{
		ptr->cmd = ft_strdup(split[*n]);
		if (access(ptr->cmd, X_OK) != 0)
			getpath(ptr, envp);
	}
	if (split[*n])
		ptr->arg = append_arg(ptr->arg, split[(*n)++]);
}
