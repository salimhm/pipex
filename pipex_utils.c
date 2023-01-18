/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmimi <shmimi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:52:41 by shmimi            #+#    #+#             */
/*   Updated: 2023/01/18 12:58:11 by shmimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
