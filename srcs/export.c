/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:30:16 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/13 23:05:37 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if the environmnent is valid or not
// valid --> 1
// not valid --> 0
static int	check_valid(char *envv)
{
	int	equal;

	equal = 0;
	while (*envv)
	{
		if (*envv == '=')
			equal = 1;
		envv++;
	}
	if (equal)
		return (1);
	return (0);
}

static void	set_index(int ind[3], char **table, char **add)
{
	ind[0] = 0;
	ind[1] = 0;
	ind[2] = 0;
	while (add[++(ind[0])])
		if (check_valid(add[ind[0]]))
			ind[1]++;
	while (table[ind[2]])
		(ind[2])++;
}

static char	**dup_add_table(char **table, char **add)
{
	char	**ret;
	int		ind[3];

	set_index(ind, table, add);
	ret = malloc((ind[1] + ind[2] + 1) * sizeof(char *));
	ret[(ind[1])-- + ind[2]] = 0;
	while ((ind[0])--)
		if (check_valid(add[ind[0]]))
			ret[ind[2] + (ind[1])--] = str_dup(add[ind[0]]);
	while ((ind[2])--)
	{
		if (ind[2])
			ret[ind[2]] = table[ind[2]];
		else
			ret[0] = str_dup(table[0]);
	}
	free(*table);
	free(table);
	return (ret);
}

void	export(t_cmd *command, char ***envp)
{
	*envp = dup_add_table(*envp, command->arg);
}
