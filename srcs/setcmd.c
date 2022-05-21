/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:23:44 by tgrivel           #+#    #+#             */
/*   Updated: 2022/05/21 15:45:34 by tgrivel          ###   ########.fr       */
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

static char	**dupntab(char **tab, int start, int end)
{
	char	**ret;

	ret = malloc((end - start + 1) * sizeof(char *));
	if (ret == 0)
		return (0);
	ret[end - start] = 0;
	while (end-- - start)
		ret[end - start] = str_dup(tab[end]);
	return (ret);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	return (new);
}

void	setcmd(t_cmd *cmd1, char **split)
{
	int	n;
	int	offset;

	n = 0;
	offset = 0;
	while (split[n])
	{
		cmd1->cmd = str_dup(split[n]);
		getpath(cmd1);
		while (split[n] && str_cmp(split[n], "|"))
			n++;
		cmd1->arg = dupntab(split, offset, n);
		offset = n + 1;
		if (split[n] != 0)
		{
			cmd1->next = new_cmd();
			cmd1 = cmd1->next;
			cmd1->next = 0;
			n++;
		}
	}
	free_tab(&split);
}
