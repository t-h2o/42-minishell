/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:23:44 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/10 15:10:10 by melogr@phy       ###   ########.fr       */
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

static t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->next = 0;
	new->cmd = 0;
	new->arg = 0;
	return (new);
}

static char
	**append_arg(char **args, char *app)
{
	char	**ret;
	int		n;

	n = 0;
	if (args)
	{
		while (args[n])
			n++;
	}
	ret = malloc((n + 2) * sizeof(char *));
	ret[n + 1] = 0;
	ret[n] = str_dup(app);
	while (n--)
		ret[n] = args[n];
	free(args);
	return (ret);

	// 0: "12"
	// 1: 0
}

// set the line in cmd struct
void	setcmd(t_line *input, char **split)
{
	int		n;
	t_cmd	*ptr;

	n = 0;
	ptr = new_cmd();
	input->cmds = ptr;
	while (split[n])
	{
		if (str_cmp(split[n], "<") && ++n)
		{
			input->inf.file = str_dup(split[n++]);
			input->inf.flag = O_RDONLY;
		}
		if (split[n] && str_cmp(split[n], ">") && ++n)
		{
			input->ouf.file = str_dup(split[n++]);
			input->ouf.flag = O_CREAT | O_RDWR | O_TRUNC;
		}
		if (split[n] && str_cmp(split[n], "|") && ++n)
		{
			ptr->next = new_cmd();
			ptr = ptr->next;
		}
		if (split[n] && ptr->cmd == 0)
		{
			ptr->cmd = str_dup(split[n]);
			if (access(ptr->cmd, X_OK) != 0)
				getpath(ptr);
		}
		if (split[n])
			ptr->arg = append_arg(ptr->arg, split[n++]);
	}
	free_tab(&split);
}
