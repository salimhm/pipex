#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);


#endif