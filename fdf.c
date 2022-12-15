/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:57 by adpachec          #+#    #+#             */
/*   Updated: 2022/12/15 13:54:11 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_error(void)
{
	int	err;

	err = errno;
	perror(strerror(err));
	exit(err);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *) s;
	i = 0;
	while (i < n && n > 0)
	{
		ptr[i] = 0;
		++i;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	const size_t	len = count * size;

	if (!count)
		return (malloc(0));
	if (len / count != size)
		return (NULL);
	ptr = (void *) malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

void	ft_free_matrix_char(char **matrix)
{
	size_t	i;

	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
}

void	ft_free_matrix_long(t_map **matrix)
{
	size_t	i;

	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	while (*str && (*str == 32 || (*str >= 9 && *str <= 13)))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		++str;
	}
	result = 0;
	while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str - '0') * sign;
		if (result > INT_MAX)
			return (-1);
		else if (result < INT_MIN)
			return (0);
		++str;
	}
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	size_t			i;
	const size_t	len_s1 = ft_strlen(s1);

	if (!s2 && s1)
		return (s1);
	str = (char *) malloc(sizeof(char) * (len_s1 + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	if (s1)
	{
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
	}
	i = -1;
	while (s2[++i])
		str[len_s1 + i] = s2[i];
	str[len_s1 + i] = '\0';
	free (s1);
	free (s2);
	return (str);
}

int	get_size_map(char **argv)
{
	int	i;

	i = -1;
	return (i);
}

char	*read_map(char **argv)
{
	int			i;
	int			fd;
	char		*buf;
	char		*map;
	const int	size_map = get_size_map(argv);

	fd = open(argv[1], O_RDONLY);
	map = NULL;
	buf = NULL;
	while (buf || map == NULL)
	{
		buf = get_next_line(fd);
		map = ft_strjoin(map, buf);
	}
	close(fd);
	return (map);
}

int	ft_size_map(t_map **map)
{
	int	size;
	int	i;
	int	j;

	size = 0;
	if (!map || !map[0])
		return (0);
	i = -1;
	while (map[++i])
		++size;
	return (size);
}

int	ft_num_in_row(char **row)
{
	int	i;
	int	size;

	size = 0;
	if (!row || !row[0])
		return (size);
	i = -1;
	while (row[++i])
		++size;
	return (size);
}

void	init_new_map(t_map **new_map, t_map **map, char **row)
{
	int			i;
	int			j;
	int			k;
	const int	size_row = ft_num_in_row(row);

	i = -1;
	if (map)
	{
		while (map[++i])
		{
			new_map[i] = (t_map *) ft_calloc(sizeof(t_map) , size_row + 1);
			if (!new_map[i])
			{
				ft_free_matrix_long(new_map);
				exit_error();
			}
		}
		--i;
	}
	new_map[++i] = (t_map *) ft_calloc(sizeof(t_map), size_row + 1);
	if (!new_map[i])
	{
		ft_free_matrix_long(new_map);
		exit_error();
	}
}

void	get_num_colour(char **row, t_map **map, t_map **new_map)
{
	int			i;
	int			j;
	int			k;
	static int	count = 0;

	i = -1;
	if (map)
	{
		while (map[++i])
		{
			j = -1;
			while (map[i][++j].height <= INT_MAX)
				new_map[i][j].height = map[i][j].height;
			new_map[i][j].height = (long) INT_MAX + 1;
		}
		--i;
	}
	k = -1;
	j = -1;
	while (row[++k])
		new_map[i + 1][++j].height = (long) ft_atoi(row[k]);
	new_map[i + 1][++j].height = (long) INT_MAX + 1;
	// i = -1;
	// while (new_map[0][++i])
	// {
	// 	j = -1;
	// 	while (new_map[0][i][++j].height <= INT_MAX)
	// 		printf("%lu ", new_map[0][i][j].height);
	// 	printf("\n");
	// }
}

t_map	**num_to_map(char **row, t_map **map)
{
	t_map		**new_map;
	const int	size_map = ft_size_map(map);
	const int	size_row = ft_num_in_row(row);

	new_map = (t_map **) malloc(sizeof(t_map *) * (size_map + 1 + 1));
	new_map[size_map + 1] = NULL;
	if (!new_map)
		exit_error();
	init_new_map(new_map, map, row);
	get_num_colour(row, map, new_map);
	// int i = -1;
	// while (new_map[++i])
	// {
	// 	int j = -1;
	// 	while (new_map[i][++j].height <= INT_MAX)
	// 		printf("%lu ", new_map[i][j].height);
	// 	printf("\n");
	// }
	ft_free_matrix_long(map);
	ft_free_matrix_char(row);
	return (new_map);
}

t_map	**build_map(char *ch_map)
{
	int		i;
	int		j;
	t_map	**map;
	char	**matrix_map;
	char	**row;

	matrix_map = ft_split(ch_map, '\n');
	i = -1;
	map = NULL;
	while (matrix_map[++i])
	{
		row = ft_split(matrix_map[i], ' ');
		map = num_to_map(row, map);
	}
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j].height <= INT_MAX)
			printf("%lu ", map[i][j].height);
		printf("\n");
	}
	ft_free_matrix_char(matrix_map);
	return (map);
}

void	fdf(void)
{
	return ;
}

int	main(int argc, char **argv)
{
	t_map	**map;
	char	*ch_map;

	//system("leaks -q a.out");
	if (argc != 2)
		return (1);
	ch_map = read_map(argv);
	map = build_map(ch_map);
	fdf();
	return (0);
}
