#include <unistd.h>
#include <stdio.h>
#include "../pipex.h"

char **get_path(char **env)
{
    char **path;
    char *envi;

    int i = 0;

    while (env[i])
    {
        if (ft_strnstr(env[i], "PATH=", 5))
        {
            envi = ft_strchr(env[i], '/');
            path = ft_split(envi, ':');
            return path;
        }
        i++;
    }
    path = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki", ':');
    return path;
}

char *check_valid_cmd(char *cmd, char **cmds)
{
    int i = 0;
    char *valid_path;
    char **tmp;

    tmp = ft_split(cmd, ' ');
    while (cmds[i])
    {
        valid_path = ft_strjoin(cmds[i], "/");
        valid_path = ft_strjoin(valid_path, tmp[0]);
        if (access(valid_path, F_OK) == 0)
        {
            return valid_path;
        }
        i++;
    }
    return 0;
}

int main(int ac, char **av, char **env)
{
    char **path = get_path(env);
    char *cmd1 = check_valid_cmd(av[1], path);
    int i = 0;
    if (access(cmd1, F_OK) == 0)
    {
        printf("=> %s\n", cmd1);
        while (av[1][i])
        {
            if (av[1][i] == '"')
            {
                char **test = ft_split(av[1], '"');
                printf("=> %s\n", cmd1);
                execve(cmd1, test, env);
            }
            i++;
        }
    }
}