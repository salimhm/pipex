/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:04:17 by shmimi            #+#    #+#             */
/*   Updated: 2023/01/21 00:14:02 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_conditions_child1(char *argv2, char **env)
{
	char	**test;
	int		i;

	i = 0;
	if ((argv2[0] != '.') && access(argv2, F_OK | X_OK) == 0)
	{
		test = ft_split(argv2, ' ');
		execve(argv2, test, env);
	}
	else if (access(argv2, F_OK | X_OK) == 0 && !ft_strchr(argv2, ' '))
	{
		test = ft_split(argv2, ' ');
		execve(argv2, test, env);
	}
}

void	ft_conditions_child2(char *argv2, char **env)
{
	char	**path;
	char	**test;
	char	*cmd1;
	int		i;

	path = get_path(env);
	cmd1 = check_valid_cmd(argv2, path);
	i = 0;
	if (access(cmd1, F_OK) == 0)
	{
		while (argv2[i])
		{
			if (argv2[i] == '"')
			{
				test = ft_split(argv2, '"');
				execve(cmd1, test, env);
			}
			i++;
		}
	}
}

void	ft_conditions_child3(char *argv2, char **env)
{
	int		i;
	char	**path;
	char	**test;
	char	*cmd1;

	path = get_path(env);
	i = 0;
	while (argv2[i])
	{
		test = ft_split(argv2, ' ');
		if (argv2[i] == ' ')
		{
			if (access(test[0], F_OK & X_OK) == 0)
			{
				cmd1 = test[0];
				break ;
			}
		}
		else if (access(test[0], F_OK) != 0)
			cmd_error(argv2);
		else if (access(argv2, X_OK | R_OK) != 0)
			no_xr_perm(argv2);
		i++;
	}
}

void	ft_conditions_child4(char *argv2, char **env)
{
	char	*cmd1;
	char	**path;
	char	**test;

	path = get_path(env);
	cmd1 = check_valid_cmd(argv2, path);
	if (access(check_valid_cmd(cmd1, path), F_OK) == 0)
	{
		test = ft_split(ft_strrchr(argv2, '/'), ' ');
		execve(check_valid_cmd(cmd1, path), test, env);
	}
	else if (access(check_valid_cmd(cmd1, path), F_OK) != 0)
		cmd_error(argv2);
}

void	ft_conditions_child5(char *argv2, char **env)
{
	char	*cmd1;
	char	**cmds;
	char	**path;

	path = get_path(env);
	cmd1 = check_valid_cmd(argv2, path);
	cmds = ft_split(argv2, ' ');
	if (access(cmd1, F_OK) != 0)
		cmd_error(argv2);
	execve(cmd1, cmds, env);
}
