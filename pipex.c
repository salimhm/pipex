/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 03:36:13 by shmimi            #+#    #+#             */
/*   Updated: 2023/01/18 13:10:58 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char *argv1, int fds[2])
{
	int	infile;

	close(0);
	infile = open(argv1, O_RDONLY | O_CREAT, 0666);
	if (infile == -1)
		exit(1);
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
}

char	**get_path(char *const *env)
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
	char	**tmp;

	i = 0;
	tmp = ft_split(cmd, ' ');
	while (cmds[i])
	{
		valid_path = ft_strjoin(cmds[i], "/");
		valid_path = ft_strjoin(valid_path, tmp[0]);
		if (access(valid_path, F_OK) == 0)
			return (valid_path);
		i++;
	}
	return (0);
}

void	*cmd_error(char *cmd)
{
	char	*cmdd;

	cmdd = ft_strjoin("pipex: ", cmd);
	cmdd = ft_strjoin(cmdd, ": command not found\n");
	write(2, cmdd, ft_strlen(cmdd));
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	char	**path;
	int		fds[2];
	int		id;
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
		id = fork();
		if (id > 0)
		{
			cmd2 = check_valid_cmd(argv[3], path);
			parent(argv[4], fds);
			ft_fork_parent(cmd2, argv[3], env, path);
		}
	}
	else
		exit(EXIT_FAILURE);
}
