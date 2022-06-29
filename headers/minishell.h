/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:13:48 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/29 16:28:59 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# define BUFFER_SIZE 42

// INCLUDES

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>

# include	<readline/readline.h>
# include	<readline/history.h>

# include	<termios.h>

# include	<signal.h>

# include	<errno.h>

# include	<fcntl.h>

# include	<sys/types.h>
# include	<sys/wait.h>
# include	<sys/stat.h>

int		g_exit_value;

// STRUCTURE

// cmd:  name of the command
// arg:  arguments of the command
// next: pointer on the next command
typedef struct s_cmd {
	char			*cmd;
	char			**arg;
	struct s_cmd	*next;
}	t_cmd;

// file is the path of the file
// flag for open the file
typedef struct s_file {
	char	*file;
	char	*eof;
	int		flag;
}	t_file;

// inf:  input file
// ouf:  output file
// cmds: pointer to cmds
// loop: if true, repeat readline
typedef struct s_line {
	t_file	inf;
	t_file	ouf;
	t_cmd	*cmds;
	int		loop;
}	t_line;

typedef struct s_params {
	int		len;
	int		tmp;
	int		td;
	int		type;
}	t_params;

// READLINE

void	rl_replace_line(const char *s, int n);

// BUILD

int		check_build(t_cmd *cmd1, char **env);
char	*getpwd(void);
void	pwd(void);
void	env(char **envp);
void	echo(t_cmd *cmd1);
void	cd(t_cmd *command, char ***envp);

// PARSING

char	*parse(t_line *inputs, char *line, char **envp);
char	*line_env(char *line, char **envp);
char	*line_exitval(char *line);
char	*line_space(char *line);
char	*trim_space(char *line);
char	**line_sep(char *line);
void	setcmd(t_line *inputs, char **split, char **envp);

// EXECUTION

void	exec_cmd(t_line *inputs, char ***envp);

//	ENVP

char	**dup_envp(char **envp);
void	export(t_cmd *command, char ***envp);
void	print_export(char **envp);
void	export_pwd(char ***envp, char *newpath);
void	unset(t_cmd *command, char ***envp);
char	*my_getenv(char *s, char **envp);

//	UTILS

void	free_tab(char ***tab);
void	free_str(char **s);
int		check_failure(char *file);
void	free_inputs(t_line *inputs);
void	errmsg(char *msg, char *cmd);
char	*ft_strdup(char *s);
char	**split(char *line, char *sep);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strndup(char *str, int n);
void	*ft_memcpy(void *dst, const void *src, size_t	n);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
char	*ft_itoa(int n);
char	**append_arg(char **args, char *app);
int		check_equal(char *env);
int		can_i_touch(char *line, char *pos);
void	init_params(t_params *p);

// GET-NEXT-LINE

char	*get_next_line(int fd);
void	here_doc(char *eof);

// SIGNALS

void	sig_int(int n);
void	sig_quit(int n);

#endif /* MINISHELL_H */
