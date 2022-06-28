/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:40:23 by ldominiq          #+#    #+#             */
/*   Updated: 2022/06/28 18:45:07 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	get_len_util(int *len, char *line, int *i)
{
	printf("EHEHEH........\n");
	*len += 2;
	while (line[*i] && line[*i] != '\'' && ++*i)
		*len += 1;
	if (line[*i] == 0)
		return (1);
	*i += 1;
	return (0);
}