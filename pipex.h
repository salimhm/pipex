/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:10:14 by shmimi            #+#    #+#             */
/*   Updated: 2023/01/21 00:35:48 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

//libft
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//ft_errors
void	*cmd_error(char *cmd);
void	*no_xr_perm(char *cmd);
void	*no_such_file(char *cmd);
void	no_input(void);

//child
void	child(char *argv1, int fds[2]);
void	ft_fork(char *argv1);
void	ft_conditions_child1(char *argv2, char **env);
void	ft_conditions_child2(char *argv2, char **env);
void	ft_conditions_child3(char *argv2, char **env);
void	ft_conditions_child4(char *argv2, char **env);
void	ft_conditions_child5(char *argv2, char **env);
void	ft_fork_child(char *argv1, char *argv2, int fds[2], char **env);
void	ft_fork_child_check(char *argv1, char *argv2, int fds[2], char **env);

//parent
void	parent(char *argv4, int fds[2]);
void	ft_conditions_parent1(char *argv3, char **env);
void	ft_conditions_parent2(char *cmd2, char *argv3, char **env, char **path);
void	ft_conditions_awk(char *argv3, char **path, char **env, int k);
void	ft_conditions_parent3(char *cmd2, char *argv3, char **env);
void	ft_conditions_parent_test(char *argv3, char *cmd2, char **env,
			char **path);
void	ft_fork_parent(char *cmd2, char *argv3, char **env, char **path);
void	check(char **path, char *argv2, char *argv3, char **env);
void	ft_fork_error(void);
void	fork_check(char *argv3);

//pipex
char	**get_path(char **env);
char	*check_valid_cmd(char *cmd, char **cmds);

//free
void	free2d(char **arg);
void	double_free2d(char **arg1, char **arg2);

#endif