/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:30:16 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/06/19 13:19:41 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count length of the table
static int	count(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// z is shorter than zz
// Z is shorter than z
// a is shorter than b
// if s1 is shorter than s2 --> 1
// else --> 0
static int	compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	if (s1[i] == 0)
		return (1);
	if (s1[i] < s2[i])
		return (0);
	return (1);
}

// Swap the address
static inline void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// Sort the table by alphabetics
static void	sort(char **table)
{
	int	i;
	int	j;

	i = 0;
	while (table[i])
	{
		j = 0;
		while (table[j])
		{
			if (compare(table[i], table[j]) == 0)
			{
				swap(&(table[i]), &(table[j]));
				i--;
				break ;
			}
			j++;
		}
		i++;
	}
}

// Print export
void	print_export(char **envp)
{
	char	**table;
	int		tmp;
	int		n;

	if (!envp || !envp[0])
		return ;
	n = count(envp);
	table = malloc((n + 1) * sizeof(char *));
	table[n] = 0;
	tmp = n;
	while (tmp--)
		table[tmp] = envp[tmp];
	sort(table);
	n = 0;
	while (table[n])
	{
		printf("declare -x %s\n", table[n]);
		++n;
	}
	free(table);
}
