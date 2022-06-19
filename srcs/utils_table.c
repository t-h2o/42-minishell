/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:35:08 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/19 13:35:41 by melogr@phy       ###   ########.fr       */
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
	ret[n + 1] = 0;
	ret[n] = str_dup(app);
	while (n--)
		ret[n] = args[n];
	free(args);
	return (ret);
}
