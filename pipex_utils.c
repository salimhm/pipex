#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static int	count_words(char *s, char delimeter)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == delimeter && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != delimeter && s[i])
			i++;
		count++;
	}
	return (count);
}

static int	count_chars(char *s, char c, int *st)
{
	int	i;

	i = 0;
	while (s[*st] != c && s[*st])
	{
		i++;
		(*st)++;
	}
	return (i);
}

static void	assign(char *s, char delimeter, char **tab, int word_counts)
{
	int	i;
	int	fixed;
	int	second_dimension;

	i = 0;
	fixed = 0;
	while (i < word_counts)
	{
		second_dimension = 0;
		while (s[fixed] == delimeter && s[fixed])
			fixed++;
		while (s[fixed] != delimeter && s[fixed])
			tab[i][second_dimension++] = s[fixed++];
		tab[i][second_dimension] = 0;
		i++;
	}
	tab[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;
	int		cw;
	int		st;

	i = 0;
	st = 0;
	if (s)
	{
		cw = count_words((char *)s, c);
		tab = (char **)malloc(sizeof(char *) * (cw + 1));
		if (!tab)
			return (0);
		while (i < cw)
		{
			while (s[st] == c && s[st])
				st++;
			tab[i++] = (char *)malloc(count_chars((char *)s, c, &st) + 1);
			if (!s[i - 1])
				return (0);
		}
		assign((char *)s, c, tab, cw);
		return (tab);
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	char	*str1;
	char	*str2;
	size_t	i;
	size_t	j;

	if (!s1)
		return (0);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	j = 0;
	if (!new_str)
		return (0);
	while (j < ft_strlen(str1))
	{
		new_str[j] = str1[j];
		j++;
	}
	while (i < ft_strlen(str2))
		new_str[j++] = str2[i++];
	new_str[j] = '\0';
	return (new_str);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*hay;
	size_t	j;
	size_t	k;

	hay = (char *)haystack;
	if (!*needle)
		return (hay);
	if (len == 0)
		return (0);
	i = 0;
	while (hay[i] && i < len)
	{
		j = 0;
		k = i;
		while (hay[k] == needle[j] && k < len)
		{
			if (needle[j + 1] == '\0')
				return (hay + i);
			j++;
			k++;
		}
		i++;
	}
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	j;

	j = ft_strlen(s);
	while (j > 0)
	{
		if (s[j] == (char)c)
		{
			s++;
			return ((char *)&s[j]);
		}
		j--;
	}
	if (s[0] == (char)c)
		return ((char *)s);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s)
	{
		i = 0;
		while (i <= ft_strlen(s) && s[i])
			write(fd, &s[i++], 1);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n && ss1[i] != '\0')
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (ss1[i] == '\0' && i < n)
		return (ss1[i] - ss2[i]);
	return (0);
}