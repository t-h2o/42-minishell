/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:13:48 by tgrivel           #+#    #+#             */
/*   Updated: 2022/04/14 14:52:59 by tgrivel          ###   ########.fr       */
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

# include	<fcntl.h>

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
void	echo(t_cmd *cmd1);

//	PARSING

char	**args(char *line);
void	parse(t_cmd *cmd1, char *line);

//	EXECUTION

void	exec_cmd(t_cmd *cmd1);

//	UTILS

void	free_tab(char ***tab);
void	free_str(char **s);
void	free_cmd(t_cmd *cmd1);
void	errmsg(char *msg, char *cmd);
char	*str_dup(char *s);
char	**split(char *line, char *sep);
int		str_cmp(char *s1, char *s2);

#endif /* MINISHELL_H */
