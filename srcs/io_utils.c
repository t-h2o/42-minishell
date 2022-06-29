/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:10:28 by lgyger            #+#    #+#             */
/*   Updated: 2022/06/29 16:33:54 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_failure(char *file)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == -1)
	{
		printf("minishell: fatal error with stat\n");
		return (0);
	}
	if (file_stat.st_mode & S_IFDIR)
		printf("minishell: %s: is a directory\n", file);
	else if (!(file_stat.st_mode & S_IRUSR
			|| file_stat.st_mode & S_IWUSR))
		printf("minishell: %s: Permission Denied\n", file);
	return (0);
}
