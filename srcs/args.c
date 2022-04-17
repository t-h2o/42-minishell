/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <melogr@phy.to>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 02:15:03 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/04/14 15:20:55 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//	blank characters --> return 1
//	not blank characters --> return 0
static int	blank(char n, char *s)
{
	while (*s)
	{
		if (n == *s)
			return (1);
		s++;
	}
	return (0);
}

//	copy up to a white character
static char	*put_str_quote(char *s, int *i)
{
	char	*ret;
	int		len;
	int		tmp;

	len = 0;
	if (s == 0)
		return (0);
	if (s[*i + 1] == '\'')
		return (0);
	while (s[*i + len + 1] != 0 && !blank(s[*i + len + 1], "\'"))
		len++;
	ret = malloc(len + 1);
	if (ret == 0)
		return (0);
	ret[len] = 0;
	tmp = len;
	while (len--)
		ret[len] = s[*i + len + 1];
	*i += tmp + 2;
	return (ret);
}

//	copy up to a white character
static char	*put_str_blank(char *s, int *i)
{
	char	*ret;
	int		len;
	int		tmp;

	if (s[*i] == '\'')
		return (put_str_quote(s, i));
	len = 0;
	if (s == 0)
		return (0);
	while (s[*i + len] != 0 && !blank(s[*i + len], " \n\t\'"))
		len++;
	ret = malloc(len + 1);
	if (ret == 0)
		return (0);
	ret[len] = 0;
	tmp = len;
	while (len--)
		ret[len] = s[*i + len];
	*i += tmp;
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
		while (line[i] && blank(line[i], " \n\t"))
			i++;
		if (line[i] == '\'')
		{
			i++;
			if (line[i] != 0 && line[i] != '\'')
			{
				arg++;
				while (line[i] && line[i] != '\'' )
					i++;
			}
				i++;
		}
		else if (line[i] != 0)
		{
			arg++;
			while (line[i] && !blank(line[i], " \n\t\'"))
				i++;
		}
		if (line[i] == 0)
			break ;
	}
	return (arg);
}

//	transform line in arguments
char	**args(char *line)
{
	char	**ret;
	int		arg;
	int		i;

	arg = count(line);
	if (arg == 0)
		return (0);
	ret = malloc(sizeof(char *) * (arg + 1));
	if (ret == 0)
		return (0);
	ret[arg] = 0;
	i = 0;
	arg = 0;
	while (1)
	{
		while (line[i] && blank(line[i], " \n\t"))
			i++;
		if (line[i] == 0)
			break ;
		ret[arg] = put_str_blank(line, &i);
		arg++;
		if (line[i] == 0)
			break ;
	}
	return (ret);
}
