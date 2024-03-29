/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:54:45 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/24 15:07:18 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
	{
		str = (char *) malloc(sizeof(char) * 1);
		str[0] = '\0';
		return (str);
	}
	if (len > len_s)
		str = (char *) malloc(sizeof(char) * (len_s + 1));
	else
		str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}

size_t	ft_words(char *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	if (s[0] == '\0')
		return (0);
	i = 0;
	if (s[0] != c)
	{
		++words;
		++i;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			++words;
		++i;
	}
	return (words);
}

static void	ft_free_res(char **res)
{
	size_t	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		res[i] = NULL;
		++i;
	}
	free(res);
}

static void	ft_init_matrix(char *s, char c, char **res, size_t words)
{
	size_t	j;
	size_t	temp;

	j = 0;
	while (*s != '\0' && j <= words)
	{
		temp = 0;
		while (*s == c)
			++s;
		while (*s != c && *s != '\0')
		{
			++s;
			++temp;
		}
		if (temp > 0)
		{
			res[j] = ft_substr(s - temp, 0, temp);
			if (!res[j++])
			{
				ft_free_res(res);
				return ;
			}
		}
	}
	res[j] = NULL;
}

char	**ft_split(char *s, char c)
{
	size_t	words;
	char	**res;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	res = (char **) ft_calloc(sizeof(char *), (words + 1));
	if (!res)
		return (NULL);
	ft_init_matrix(s, c, res, words);
	if (!res)
		return (NULL);
	return (res);
}
