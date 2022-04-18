/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:15:03 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/18 11:04:26 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	get_spot(char *s, int *i, int *len)
{
	while (s[*i] && s[*i] != ' ')
	{
		while (s[*i] == '\'')
		{
			(*i)++;
			while (s[*i] && s[*i] != '\'')
			{
				(*i)++;
				(*len)++;
			}
			(*i)++;
		}
		while (s[*i] && s[*i] != '\'' && s[*i] != ' ')
		{
			(*i)++;
			(*len)++;
		}
	}
}

//	copy up to a white character
static char	*put_str(char *s, int *j)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	len = 0;
	get_spot(s, &i, &len);
	ret = malloc(len + 1);
	if (ret == 0)
		return (0);
	ret[len] = 0;
	*j += i--;
	while (len > 0)
	{
		while (s[i] == '\'')
			i--;
		ret[--len] = s[i--];
	}
	return (ret);
}

static int	count(char *line)
{
	int	i;
	int	arg;

	i = 0;
	arg = 0;
	while (1)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == 0)
			break ;
		while (line[i] == '\'')
		{
			i++;
			while (line[i] != 0 && line[i] != '\'')
				i++;
			i++;
		}
		while (line[i] != 0 && line[i] != ' ')
			i++;
		arg++;
	}
	return (arg);
}

//	transform line in arguments
char	**args(char *line)
{
	char	**ret;
	int		arg;
	int		i;

	line = put_env_in_line(line);
	arg = count(line);
	if (arg == 0)
		return (0);
	ret = malloc(sizeof(char *) * (arg + 1));
	if (ret == 0)
		return (0);
	ret[arg] = 0;
	i = 0;
	arg = 0;
	while (ret[arg] != 0)
	{
		while (line[i] == ' ')
			i++;
		ret[arg] = put_str(&(line[i]), &i);
		if (ret[arg] == 0)
		{
			free_tab(&ret);
			return (0);
		}
		arg++;
	}
	free(line);
	return (ret);
}
