/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:57 by adpachec          #+#    #+#             */
/*   Updated: 2022/12/14 16:54:38 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	ft_free_matrix_long(long **matrix)
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

int	ft_size_map(long **map)
{
	int	size;
	int	i;
	int	j;

	size = 0;
	if (!map || !map[0])
		return (0);
	i = -1;
	while (map[++i])
	{
		j = -1;
		printf("size: %d\n", size);
		while (map[i][++j] <= INT_MAX)
		{
			printf("%lu ", map[i][++j]);
			++size;
		}
		printf("\n");	
	}
	printf("size: %d", size);
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

void	init_new_map(long **new_map, long **map, char **row)
{
	int	i;
	int	j;
	int	k;
	const int	size_row = ft_num_in_row(row);

	i = -1;
	if (map)
	{
		while (map[++i])
			new_map[i] = (long *) ft_calloc(sizeof(long) , size_row);
	}
	new_map[++i] = (long *) ft_calloc(sizeof(long), size_row);
}

long	**num_to_map(char **row, long **map)
{
	int			i;
	int			j;
	int			k;
	long		**new_map;
	const int	size_map = ft_size_map(map);
	const int	size_row = ft_num_in_row(row);

	new_map = (long **) malloc(sizeof(long *) * (size_map + size_row + 1));
	init_new_map(new_map, map, row);
	new_map[size_map + size_row] = NULL;
	i = -1;
	if (map)
	{
		while (map[++i])
		{
			j = -1;
			while (map[i][++j] <= INT_MAX)
				new_map[i][j] = map[i][j];
			new_map[i][j] = (long) INT_MAX + 1;
		}
	}
	k = -1;
	j = -1;
	while (row[++k])
	{
		new_map[i + 1][++j] = ft_atoi(row[k]);
	}
	new_map[i + 1][j] = (long) INT_MAX + 1;
	printf("size_row: %d", size_row);
	printf("j: %d", j);
	ft_free_matrix_long(map);
	ft_free_matrix_char(row);
	return (new_map);
}

long	**build_map(char *ch_map)
{
	int		i;
	int		j;
	long	**map;
	char	**matrix_map;
	char	**row;
	int r;

	matrix_map = ft_split(ch_map, '\n');
	i = -1;
	map = NULL;
	while (matrix_map[++i])
	{
		row = ft_split(matrix_map[++i], ' ');
		j = -1;
		printf("rows\n");
		while (row[++j])
			printf("%s ", row[j]);
		printf("\n");
		map = num_to_map(row, map);
		i = -1;
		printf("map\n");
		while (map[++i])
		{
			r = -1;
			while(map[i][++r] <= INT_MAX)
				printf("%lu ", map[i][++r]);
			printf("\n");
		}
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
	long		**map;
	char	*ch_map;

	if (argc != 2)
		return (1);
	ch_map = read_map(argv);
	map = build_map(ch_map);
	fdf();
	return (0);
}
