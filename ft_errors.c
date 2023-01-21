/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:28:17 by shmimi            #+#    #+#             */
/*   Updated: 2023/01/20 19:20:40 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*cmd_error(char *cmd)
{
	char	*cmdd;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	cmdd = ft_strjoin("pipex: ", cmds[0]);
	cmdd = ft_strjoin(cmdd, ": command not found\n");
	write(2, cmdd, ft_strlen(cmdd));
	exit(127);
}

void	*no_xr_perm(char *cmd)
{
	char	*cmdd;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	cmdd = ft_strjoin("pipex: ", cmds[0]);
	cmdd = ft_strjoin(cmdd, ": permission denied\n");
	write(2, cmdd, ft_strlen(cmdd));
	exit(126);
}

void	*no_such_file(char *cmd)
{
	char	*cmdd;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	cmdd = ft_strjoin("pipex: ", cmds[0]);
	cmdd = ft_strjoin(cmdd, ": no such file or directory\n");
	write(2, cmdd, ft_strlen(cmdd));
	exit(127);
}

void	no_input(void)
{
	write(2, "pipex: permission denied:\n", 26);
	exit(126);
}
