/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:38:09 by zdidah            #+#    #+#             */
/*   Updated: 2025/01/24 18:17:49 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
size_t	ft_arrlen(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
	}
	return ;
}

int	count_word(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '\n'))
			i++;
		if (str[i] && (str[i] != '\n'))
		{
			while (str[i] && (str[i] != '\n'))
				i++;
			count++;
		}
	}
	return (count);
}

char	**fill_word(char *str, char **res)
{
	int	i;
	int	k;
	int	j;
	int	words;

	i = 0;
	k = 0;
	j = 0;
	words = count_word(str);
	while (str[i])
	{
		while (str[i] && (str[i] != '\n'))
			i++;
		if (j == words)
			res[j] = malloc((i - k + 1) * sizeof(char));
		else
			res[j] = malloc((i - k) * sizeof(char));
		if (!res[j])
			return (free_all(res), NULL);
		while (str[i] && (str[i] == '\n'))
			i++;
		k = i;
		j++;
	}
	return (res);
}

char	**ft_split(char *str)
{
	char	**res;
	int		words;

	int(i), (j), (k);
	i = 0;
	k = 0;
	j = 0;
	words = count_word(str);
	res = malloc((count_word(str) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = fill_word(str, res);
	while (str[i])
	{
		while ((str[i]) && (str[i] != '\n'))
			res[j][k++] = str[i++];
		res[j][k++] = '\n';
		res[j][k] = '\0';
		while (str[i] && (str[i] == '\n'))
			i++;
		if (k != 0)
			j++;
		k = 0;
	}
	return (res[j] = NULL, res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i++] = s2[j++];
	}
	str[i++] = '\n';
	free(s1);
	return (str[i] = 0, str);
}
char	**ft_arrjoin(char **s1, char *s2)
{
	char	*str;
	char	**arr;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	if (!s1 && !s2)
		return (NULL);
	arr = malloc(sizeof(char *) * (ft_arrlen(s1) + 2));
	while (s1 && s1[i])
	{
		len = ft_strlen(s1[i]);
		arr[i] = malloc(sizeof(char) * (len + 1));
		i++;
	}
	if (!arr)
		return (NULL);
	i = 0;
	while (s1 && s1[j])
	{
		while (s1[j][i])
		{
			arr[j][i] = s1[j][i];
			i++;
		}
		arr[j][i] = '\0';
		j++;
		i = 0;
	}
	if (s2)
		arr[j] = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	while (s2 && s2[i])
	{
		arr[j][i] = s2[i];
		i++;
	}
	free(s1);
	return (arr[j][i] = 0, arr[j + 1] = NULL, free(s2), arr);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && !len)
		return (NULL);
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *)haystack + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || (!s1 && !s2))
		return (0);
	while (s1[i] && s2[i] && i < n - 1) 
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
