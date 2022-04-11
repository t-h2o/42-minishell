/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:13:48 by tgrivel           #+#    #+#             */
/*   Updated: 2022/04/11 23:39:51 by melogr@phy       ###   ########.fr       */
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

//	BUILD

int		check_build(char *line, char **env);
void	pwd(void);
void	env(char **envp);

#endif /* MINISHELL_H */
