/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:35:08 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/22 22:23:07 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char
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
	if (!ret)
		return (NULL);
	ret[n + 1] = 0;
	ret[n] = str_dup(app);
	while (n--)
		ret[n] = args[n];
	free(args);
	return (ret);
}
