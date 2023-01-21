/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 03:36:13 by shmimi            #+#    #+#             */
/*   Updated: 2023/01/21 23:30:41 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char *argv1, int fds[2])
{
	int	infile;

	close(0);
	if (access(argv1, F_OK | R_OK) != 0)
	{
		write(2, "pipex: no such file or directory: ", 34);
		write(2, argv1, ft_strlen(argv1));
		write(2, "\n", 1);
		exit(0);
	}
	infile = open(argv1, O_RDONLY, 0666);
	if (infile == -1)
		exit(1);
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
}

char	**get_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (env[i] == ft_strnstr(env[i], "PATH=", ft_strlen(env[i])))
		{
			path = ft_split(ft_strchr(env[i], '/'), ':');
			return (path);
		}
		i++;
	}
	i = 0;
	while (env[i++])
	{
		path = ft_split(env[i], '=');
		if (ft_strncmp(path[0], "PATH", 4) != 0)
			return (path);
	}
	path = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
			':');
	return (path);
}

char	*check_valid_cmd(char *cmd, char **cmds)
{
	int		i;
	char	*valid_path;
	char	*lol;
	char	**tmp;

	i = 0;
	tmp = ft_split(cmd, ' ');
	while (cmds[i])
	{
		lol = ft_strjoin(cmds[i], "/");
		valid_path = ft_strjoin(lol, tmp[0]);
		free(lol);
		if (access(valid_path, F_OK) == 0)
		{
			lol = malloc(ft_strlen(valid_path) + 1);
			ft_strlcpy(lol, valid_path, ft_strlen(valid_path) + 1);
			free2d(tmp);
			free(valid_path);
			return (lol);
		}
		i++;
		free(valid_path);
	}
	double_free2d(cmds, tmp);
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	char	**path;
	int		fds[2];
	char	*cmd2;

	if (argc > 4)
	{
		path = get_path(env);
		if (access(argv[2], F_OK | X_OK) == 0)
			path = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin",
					':');
		check(path, argv[2], argv[3], env);
		pipe(fds);
		ft_fork_child_check(argv[1], argv[2], fds, env);
		if (fork() > 0)
		{
			fork_check(argv[3]);
			cmd2 = check_valid_cmd(argv[3], path);
			parent(argv[4], fds);
			ft_fork_parent(cmd2, argv[3], env, path);
		}
		free2d(path);
	}
	else
		exit(EXIT_FAILURE);
}
