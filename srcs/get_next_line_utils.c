/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:54:09 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/22 16:12:07 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*ptr;
	size_t	len;

	if (!count || !size)
		return (malloc(0));
	len = count * size;
	if (len / count != size)
		return (NULL);
	ptr = (char *) malloc(len);
	if (!ptr)
		return (NULL);
	while (len)
		ptr[--len] = 0;
	return (ptr);
}

size_t	ft_strlen_gnl(char *s, int gnl)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	if (!gnl)
	{
		while (s[len])
			++len;
	}
	else
	{
		while (s[len] && s[len] != '\n')
			++len;
	}
	return (len);
}

int	ft_strchr_gnl(char *s, int c)
{
	int		i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (s[i] == (char) c)
			return (1);
	}
	return (0);
}

char	*ft_memcpy_gnl(char *dst, char *src)
{
	int	j;

	j = -1;
	if (!dst && !src)
		return (NULL);
	while (src[++j])
		dst[j] = src[j];
	free (src);
	return (dst);
}

char	*ft_strjoin_gnl(char *line, char **save_read)
{
	char			*str;
	int				i;
	const size_t	len_line = ft_strlen_gnl(line, 0);
	const size_t	len_save_read = ft_strlen_gnl(*save_read, 1);

	str = (char *) ft_calloc_gnl(1, sizeof(char) * (len_line + \
	len_save_read + 2));
	if (!str)
		return (NULL);
	i = -1;
	if (line)
	{
		while (line[++i])
			str[i] = line[i];
	}
	str = write_line(str, &(*save_read));
	free (line);
	return (str);
}
