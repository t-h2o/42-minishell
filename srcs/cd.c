/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:01:54 by tgrivel           #+#    #+#             */
/*   Updated: 2022/06/28 12:50:19 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void why(char *path)
{
	struct	stat	file;

	stat(path, &file);
	if (!(file.st_mode & S_IFDIR))
		printf("cd: not a directory: %s\n", path);
}


static char
	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = (char *)malloc(len);
	if (!str)
		return (0);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	return (str);
}

static void	change_envp(char ***envp, char *oldpath)
{
	char	*pwd;
	char	*newpwd;
	char	*oldpwd;

	pwd = getpwd();
	newpwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	export_pwd(envp, newpwd);
	free(newpwd);
	oldpwd = ft_strjoin("OLDPWD=", oldpath);
	export_pwd(envp, oldpwd);
	free(oldpwd);
}

void	cd(t_cmd *command, char ***envp)
{
	char	*home;
	char	*oldpath;

	oldpath = getpwd();
	if (command->arg[1] != 0)
	{
		if (chdir(command->arg[1]) != -1)
			change_envp(envp, oldpath);
		else
			why(command->arg[1]);
	}
	else
	{
		home = my_getenv("HOME", *envp);
		if (chdir(home) == 0)
			change_envp(envp, oldpath);
	}
	free(oldpath);
}
