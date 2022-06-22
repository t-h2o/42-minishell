/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:23:44 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/22 22:12:23 by ldominiq         ###   ########.fr       */
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

static t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->next = 0;
	new->cmd = 0;
	new->arg = 0;
	return (new);
}

static void	fill_line(t_line *input, char **split, int *n)
{
	if (split[*n] && ft_strcmp(split[*n], "<") && ++(*n))
	{
		input->inf.file = str_dup(split[(*n)++]);
		input->inf.flag = O_RDONLY;
	}
	if (split[*n] && ft_strcmp(split[*n], "<<") && ++(*n))
	{
		input->inf.file = str_dup("/tmp/.minishell-here_doc");
		input->inf.eof = str_dup(split[(*n)++]);
		input->inf.flag = O_RDONLY;
	}
	if (split[*n] && ft_strcmp(split[*n], ">") && ++(*n))
	{
		input->ouf.file = str_dup(split[(*n)++]);
		input->ouf.flag = O_CREAT | O_RDWR | O_TRUNC;
	}
}

// set the line in cmd struct
void	setcmd(t_line *input, char **split, char **envp)
{
	int		n;
	t_cmd	*ptr;

	n = 0;
	ptr = new_cmd();
	if (ptr)
	{
		input->cmds = ptr;
		while (split[n])
		{
			fill_line(input, split, &n);
			if (split[n] && ft_strcmp(split[n], "|") && ++n)
			{
				ptr->next = new_cmd();
				ptr = ptr->next;
			}
			if (split[n] && ptr->cmd == 0)
			{
				ptr->cmd = str_dup(split[n]);
				if (access(ptr->cmd, X_OK) != 0)
					getpath(ptr, envp);
			}
			if (split[n])
				ptr->arg = append_arg(ptr->arg, split[n++]);
		}
	}
	free_tab(&split);
}
