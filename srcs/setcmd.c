/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:23:44 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/30 22:16:27 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == 0)
		return (0);
	new->next = 0;
	new->cmd = 0;
	new->arg = 0;
	return (new);
}

static void	fill_line(t_line *input, char **split, int *n)
{
	if (split[*n] && ft_strcmp(split[*n], "<") && ++(*n))
	{
		input->inf.file = ft_strdup(split[(*n)++]);
		input->inf.flag = O_RDONLY;
	}
	if (split[*n] && ft_strcmp(split[*n], "<<") && ++(*n))
	{
		input->inf.file = ft_strdup("/tmp/.minishell-here_doc");
		input->inf.eof = ft_strdup(split[(*n)++]);
		input->inf.flag = O_RDONLY;
	}
	if (split[*n] && ft_strcmp(split[*n], ">") && ++(*n))
	{
		input->ouf.file = ft_strdup(split[(*n)++]);
		input->ouf.flag = O_CREAT | O_RDWR | O_TRUNC;
	}
	if (split[*n] && ft_strcmp(split[*n], ">>") && ++(*n))
	{
		input->ouf.file = ft_strdup(split[(*n)++]);
		input->ouf.flag = O_CREAT | O_APPEND | O_WRONLY;
	}
}

// set the line in cmd struct
void	setcmd(t_line *input, char **split, char **envp)
{
	int		n;
	t_cmd	*ptr;

	n = 0;
	ptr = new_cmd();
	if (ptr == 0)
		return ;
	input->cmds = ptr;
	while (split[n])
	{
		fill_line(input, split, &n);
		if (split[n] && ft_strcmp(split[n], "|") && ++n)
		{
			if (!split[n])
				ptr->arg = append_arg(ptr->arg, split[n - 1]);
			else
			{
				ptr->next = new_cmd();
				if (ptr->next == 0)
					return ;
				ptr = ptr->next;
			}
		}
		dup_cmd(split, envp, &n, ptr);
	}
	free_tab(&split);
}
