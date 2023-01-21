/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:58:52 by shmimi            #+#    #+#             */
/*   Updated: 2023/01/21 00:09:23 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_fork_child(char *argv1, char *argv2, int fds[2], char **env)
{
	char	**test;

	test = ft_split(argv2, ' ');
	if (ft_strlen(argv2) == 0)
		no_xr_perm(argv2);
	child(argv1, fds);
	ft_conditions_child1(argv2, env);
	ft_conditions_child2(argv2, env);
	if (argv2[0] == '/' || argv2[0] == '.')
	{
		if (access(test[0], F_OK) == 0)
			execve(test[0], test, env);
		ft_conditions_child3(argv2, env);
		ft_conditions_child4(argv2, env);
	}
	else
		ft_conditions_child5(argv2, env);
}

void	ft_fork_parent(char *cmd2, char *argv3, char **env, char **path)
{
	char	**test;
	int		k;

	k = 0;
	if (argv3[0] == '/' || argv3[0] == '.')
	{
		test = ft_split(argv3, ' ');
		if (access(test[0], F_OK) == 0)
			execve(test[0], test, env);
		ft_conditions_parent1(argv3, env);
		free(cmd2);
		cmd2 = ft_strrchr(argv3, '/');
		execve(cmd2, test, env);
		ft_conditions_parent2(cmd2, argv3, env, path);
		free2d(test);
	}
	if (ft_strnstr(argv3, "awk", ft_strlen(argv3)))
		ft_conditions_awk(argv3, path, env, k);
	else
		ft_conditions_parent3(cmd2, argv3, env);
}

void	check(char **path, char *argv2, char *argv3, char **env)
{
	if (ft_strlen(argv2) == 0)
		write(2, "pipex: permission denied:\n", 27);
	if (path == NULL)
	{
		if (access(argv2, F_OK | X_OK) == 0)
			execve(argv2, ft_split(argv2, ' '), env);
		else
		{
			cmd_error(argv2);
			cmd_error(argv3);
			exit(127);
		}
	}
}

void	ft_fork_error(void)
{
	write(2, "Error in fork", 13);
	exit(1);
}

void	ft_fork_child_check(char *argv1, char *argv2, int fds[2], char **env)
{
	int	id;

	id = fork();
	if (id < 0)
		ft_fork_error();
	if (id == 0)
		ft_fork_child(argv1, argv2, fds, env);
}
