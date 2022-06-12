/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:30:16 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/12 11:09:47 by melogr@phy       ###   ########.fr       */
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

static char	**dup_add_table(char **table, char **add)
{
	char	**ret;
	int		i;
	int		ladd;
	int		ltab;

	ladd = 0;
	ltab = 0;
	i = 0;
	while (add[++i])
		if(check_valid(add[i]))
			ladd++;

	if (ladd == 0)
		return (table);
	while (table[ltab])
		ltab++;

	ret = malloc((ladd + ltab + 1) * sizeof(char *));
	ret[ladd-- + ltab] = 0;
	while (i--)
		if (check_valid(add[i]))
			ret[ltab + ladd--] = str_dup(add[i]); 
	
	while (ltab--)
		ret[ltab] = table[ltab];

	free(table);
	return (ret);
}

void	export(t_cmd *command, char ***envp)
{
	*envp = dup_add_table(*envp, command->arg);
}
