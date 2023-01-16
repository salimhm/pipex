
#include "pipex.h"

char **get_path(char *const *env)
{
    char **path;
    char *envi;
    char **test;

    int i = 0;

    while (env[i])
    {
        if (env[i] == ft_strnstr(env[i], "PATH=", ft_strlen(env[i])))
        {
            envi = ft_strchr(env[i], '/');
            path = ft_split(envi, ':');
            return path;
        }
        i++;
    }
    i = 0;
    while (env[i])
    {
        test = ft_split(env[i], '=');
        if (ft_strncmp(test[0], "PATH", 4) != 0)
        {
            path = NULL;
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
            return valid_path;
        i++;
    }
    return 0;
}

void *cmd_error(char *cmd)
{
    char *cmdd;
    cmdd = ft_strjoin("pipex: ", cmd);
    cmdd = ft_strjoin(cmdd, ": command not found\n");
    write(2, cmdd, ft_strlen(cmdd));
    return 0;
}

int main(int argc, char *argv[], char **env)
{
    if (argc > 4)
    {
        char **path = NULL;
        char **cmds;
        char **cmds2;
        char *cmd1;
        char *cmd2;

        int fds[2];
        path = get_path(env);
        if (access(argv[2], F_OK | X_OK) == 0)
            path = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki", ':');
        if (path == NULL)
        {
            if (access(argv[2], F_OK | X_OK) == 0)
            {
                char **test = ft_split(argv[2], ' ');
                execve(argv[2], test, env);
            }
            else
            {
                cmd_error(argv[2]);
                cmd_error(argv[3]);
                exit(127);
            }
        }
        pipe(fds);
        cmds = ft_split(argv[2], ' ');
        cmds2 = ft_split(argv[3], ' ');

        cmd1 = check_valid_cmd(argv[2], path);
        cmd2 = check_valid_cmd(argv[3], path);

        int id = fork();
        if (id == -1)
        {
            //perror("Error in fork");
            write(2, "Error in fork", 13);
			exit(1);
        }
        if (id == 0)
        {
            close(0);
            int infile;
            infile = open(argv[1], O_RDONLY | O_CREAT, 0666);
            if (infile == -1)
                return 1;

            if (access(argv[1], R_OK) == 0)
            {
                dup2(fds[1], 1);
                close(fds[0]);
                close(fds[1]);

                int i = 0;

                if ((argv[2][0] != '.') && access(argv[2], F_OK | X_OK) == 0)
                {
                    char **test = ft_split(argv[2], ' ');
                    execve(argv[2], test, env);
                }
                else if (access(argv[2], F_OK | X_OK) == 0 && !ft_strchr(argv[2], ' '))
                {
                    char **test = ft_split(argv[2], ' ');
                    execve(argv[2], test, env);
                }
                else if (access(cmd1, F_OK) == 0)
                {
                    while (argv[2][i])
                    {
                        if (argv[2][i] == '"')
                        {
                            char **test = ft_split(argv[2], '"');
                            execve(cmd1, test, env);
                        }
                        i++;
                    }
                }
                i = 0;
                if (argv[2][0] == '/' || argv[2][0] == '.')
                {
                    while (argv[2][i])
                    {
                        if (argv[2][i] == ' ')
                        {
                            char **xd = ft_split(argv[2], ' ');
                            if (access(xd[0], F_OK) == 0 && access(xd[0], X_OK) == 0)
                            {
                                cmd1 = xd[0];
                                break;
                            }
                        }
                        i++;
                    }
                    if (access(check_valid_cmd(cmd1, path), F_OK) == 0)
                    {
                        char *tmp = ft_strrchr(argv[2], '/');
                        char **tmp2 = ft_split(tmp, ' ');
                        execve(check_valid_cmd(cmd1, path), tmp2, env);
                    }
                }
                else
                {
                    if (access(cmd1, F_OK) != 0)
                    {
                        cmd_error(argv[2]);
                        exit(127);
                    }
                    execve(cmd1, cmds, env);
                    exit(126);
                }
            }
        }
        else
        {
            close(1);
            int outfile;
            outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
            if (outfile == -1)
                return 1;

            if (access(argv[3], F_OK | X_OK) == 0)
                path = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki", ':');
            if (access(argv[4], R_OK) == 0)
            {
                close(0);
                close(fds[1]);
                dup2(fds[0], 0);
                close(fds[0]);

                int j = 0;

                if (argv[3][0] == '/' || argv[3][0] == '.')
                {
                    while (argv[3][j])
                    {
                        if (argv[3][j] == ' ')
                        {
                            char **xd = ft_split(argv[3], ' ');
                            if (access(xd[0], F_OK) == 0)
                                cmd2 = xd[0];
                        }
                        else
                            cmd2 = ft_strrchr(argv[3], '/');
                        j++;
                    }
                    if (access(check_valid_cmd(cmd2, path), F_OK | X_OK) == 0)
                    {
                        char *tmp = ft_strrchr(argv[3], '/');
                        char **tmp2 = ft_split(tmp, ' ');
                        execve(check_valid_cmd(cmd2, path), tmp2, env);
                    }
                    else if (access(argv[3], F_OK | X_OK) == 0)
                    {
                        char **tmp2 = ft_split(argv[3], ' ');
                        execve(argv[3], tmp2, env);
                    }
                }
                else if (ft_strnstr(argv[3], "awk", ft_strlen(argv[3])))
                {
                    char **test;
                    char **awk;
                    int k = 0;
                    while (argv[3][k])
                    {
                        if (argv[3][k] == 39)
                        {
                            test = ft_split(argv[3], 39);
                            awk = ft_split(test[0], ' ');
                            test[0] = awk[0];
                        }
                        else if (argv[3][k] == '"')
                        {
                            test = ft_split(argv[3], '"');
                            awk = ft_split(test[0], ' ');
                            test[0] = awk[0];
                        }
                        k++;
                    }
                    execve(check_valid_cmd(awk[0], path), test, env);
                }
                else
                {
                    if (access(cmd2, F_OK) != 0)
                    {
                        cmd_error(argv[3]);
                        exit(127);
                    }
                    execve(cmd2, cmds2, env);
                    exit(126);
                }
            }
        }
    }
    else
        exit(EXIT_FAILURE);
}
