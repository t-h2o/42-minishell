/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:13:48 by tgrivel           #+#    #+#             */
/*   Updated: 2022/04/12 22:36:40 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

//	INCLUDES

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>

# include	<readline/readline.h>
# include	<readline/history.h>

# include	<termios.h>

# include	<signal.h>

# include	<errno.h>

//	STRUCTURE

//	cmd:	name of the command
//	arg:	arguments of the command
//	next:	pointer on the next command
typedef struct s_cmd	t_cmd;
struct s_cmd {
	char	*cmd;
	char	**arg;
	t_cmd	*next;
};

//	BUILD

int		check_build(t_cmd *cmd1, char **env);
void	pwd(void);
void	env(char **envp);

//	PARSING

void	parse(t_cmd *cmd1, char *line);

//	UTILS

void	free_str(char **s);
void	free_cmd(t_cmd *cmd1);
char	*str_dup(char *s);
char	**split(char *line);

#endif /* MINISHELL_H */
