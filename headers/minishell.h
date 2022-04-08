/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:13:48 by tgrivel           #+#    #+#             */
/*   Updated: 2022/04/08 15:44:27 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

//	INCLUDES

# include	<stdio.h>
# include	<stdlib.h>

//	readline
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<unistd.h>

//	BUILD

int	check_build(char *line);

#endif /* MINISHELL_H */
