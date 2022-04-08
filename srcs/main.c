/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:09:46 by tgrivel           #+#    #+#             */
/*   Updated: 2022/04/08 15:10:59 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void
	ft_foo(int n)
{
	printf("\n\tHello World %d\n\n", n);
}

int
	main(void)
{
	char	*line;

	ft_foo(42);
	line = readline("it's the Prompt $ ");
	printf("line-->%s\n", line);
	free(line);
}
