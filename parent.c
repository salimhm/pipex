/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:02:28 by shmimi            #+#    #+#             */
/*   Updated: 2023/01/21 00:11:39 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(char *argv4, int fds[2])
{
	int	outfile;

	close(1);
	outfile = open(argv4, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (outfile == -1)
		exit(1);
	close(0);
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
}

void	ft_conditions_parent1(char *argv3, char **env)
{
	int		i;
	char	**test;

	i = 0;
	while (argv3[i])
	{
		test = ft_split(argv3, ' ');
		if (argv3[i] == ' ')
		{
			if (access(test[0], F_OK) == 0)
				execve(test[0], test, env);
		}
		else if (access(test[0], F_OK) != 0)
		{
			free2d(test);
			cmd_error(argv3);
		}
		else if (access(argv3, X_OK | R_OK) != 0)
		{
			free2d(test);
			no_xr_perm(argv3);
		}
		i++;
	}
}

void	ft_conditions_parent2(char *cmd2, char *argv3, char **env, char **path)
{
	char	**test;

	if (access(check_valid_cmd(cmd2, path), F_OK | X_OK) == 0)
	{
		test = ft_split(ft_strrchr(argv3, '/'), ' ');
		execve(check_valid_cmd(cmd2, path), test, env);
	}
	else if (access(argv3, F_OK | X_OK) == 0)
	{
		test = ft_split(ft_strrchr(argv3, '/'), ' ');
		execve(argv3, test, env);
	}
}

void	ft_conditions_awk(char *argv3, char **path, char **env, int k)
{
	char	**test;
	char	**awk;

	awk = ft_split(argv3, ' ');
	test = ft_split(argv3, ' ');
	while (argv3[k++])
	{
		if (argv3[k] == 39)
		{
			double_free2d(awk, test);
			test = ft_split(argv3, 39);
			awk = ft_split(test[0], ' ');
			ft_strlcpy(test[0], awk[0], ft_strlen(awk[0]) + 1);
		}
		else if (argv3[k] == '"')
		{
			double_free2d(awk, test);
			test = ft_split(argv3, '"');
			awk = ft_split(test[0], ' ');
			ft_strlcpy(test[0], awk[0], ft_strlen(awk[0]) + 1);
		}
		else if (!ft_strchr(argv3, ' '))
			execve(check_valid_cmd(awk[0], path), awk, env);
	}
	execve(check_valid_cmd(awk[0], path), test, env);
}

void	ft_conditions_parent3(char *cmd2, char *argv3, char **env)
{
	char	**cmds2;

	cmds2 = ft_split(argv3, ' ');
	if (access(cmd2, F_OK) != 0)
	{
		free2d(cmds2);
		cmd_error(argv3);
	}
	execve(cmd2, cmds2, env);
}
