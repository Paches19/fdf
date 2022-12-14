/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:57 by adpachec          #+#    #+#             */
/*   Updated: 2022/12/19 15:59:06 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

void	exit_error_hexa(void)
{
	int	err;

	err = errno;
	perror("Codigo de color introducido no válido\n");
	perror("El formato para una altura con color es:\n");
	perror("altura,codigo -> 0,0xFFFFFF\n");
	exit(err);
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
	matrix = NULL;
}

void	ft_free_matrix_tmap(t_map **matrix)
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
	matrix = NULL;
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

void	check_color(char *color)
{
	int	i;

	if (!color)
		return ;
	if (color[0] != '0' || color[1] != 'x')
		exit_error_hexa();
	i = 1;
	while (color[++i])
	{
		if (color[i] < '0' || (color[i] > '9' && color[i] < 'A'))
			exit_error_hexa();
		if ((color[i] > 'F' && color[i] < 'a') || color[i] > 'f')
			exit_error_hexa();
	}	
}

long int	ft_htol(char *color)
{
	int			i;
	int			base;
	const char	*c = "0xFFFFFF";
	long int	result;
	
	if (!color)
		color = (char *) c;
	check_color(color);
	i = ft_strlen(color) - 1;
	result = 0;
	base = 1;
	while (i > 1)
	{
		if (ft_isdigit(color[i]))
			result += (color[i] - 48) * base;
		else if (color[i] >= 'a' && color[i] <= 'f')
			result += (color[i] - 87) * base;
		else if (color[i] >= 'A' && color[i] <= 'F')
			result += (color[i] - 55) * base;
		base *= 16;
		--i;
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
		exit_error();
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

// int	get_size_map(char **argv)
// {
// 	int	i;

// 	i = -1;
// 	return (i);
// }

char	*read_map(char **argv)
{
	int			fd;
	char		*buf;
	char		*map;
	//const int	size_map = get_size_map(argv);

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
	const int	size_row = ft_num_in_row(row);

	i = -1;
	if (map)
	{
		while (map[++i])
		{
			new_map[i] = (t_map *) ft_calloc(sizeof(t_map) , size_row + 1);
			if (!new_map[i])
			{
				ft_free_matrix_tmap(new_map);
				exit_error();
			}
		}
		--i;
	}
	new_map[++i] = (t_map *) ft_calloc(sizeof(t_map), size_row + 1);
	if (!new_map[i])
	{
		ft_free_matrix_tmap(new_map);
		exit_error();
	}
}

void	get_num_color(char **row, t_map **map, t_map **new_map)
{
	int			i;
	int			j;
	char		**height_color;

	i = -1;
	if (map)
	{
		while (map[++i])
		{
			j = -1;
			while (map[i][++j].height <= INT_MAX)
				new_map[i][j].height = map[i][j].height;
			new_map[i][j].height = (long) INT_MAX + 1;
			while (--j >= 0)
				new_map[i][j].color = map[i][j].color;
		}
		--i;
	}
	j = -1;
	while (row[++j])
	{
		height_color = ft_split(row[j], ',');
		new_map[i + 1][j].height = (long) ft_atoi(height_color[0]);
		new_map[i + 1][j].color = (long) ft_htol(height_color[1]);
		ft_free_matrix_char(height_color);
	}
	new_map[i + 1][j].height = (long) INT_MAX + 1;
	new_map[i + 1][j].color = (long) INT_MAX + 1;
}

t_map	**num_to_map(char **row, t_map **map)
{
	t_map		**new_map;
	const int	size_map = ft_size_map(map);
	//const int	size_row = ft_num_in_row(row);

	new_map = (t_map **) malloc(sizeof(t_map *) * (size_map + 1 + 1));
	new_map[size_map + 1] = NULL;
	if (!new_map)
		exit_error();
	init_new_map(new_map, map, row);
	get_num_color(row, map, new_map);
	ft_free_matrix_tmap(map);
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
		ft_free_matrix_char(row);
	}
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j].height <= INT_MAX)
			printf("%lu ", map[i][j].height);
		printf("\n");
	}
	i = -1;
	while (map[++i])
	{
		int r = j;
		j = -1;
		while (++j < r)
			printf("%lu ", map[i][j].color);
		printf("\n");
	}
	ft_free_matrix_char(matrix_map);
	return (map);
}

void	fdf(t_map **map)
{
	void	*mlx_con;
	void	*mlx_win;
	int		x;
	int		y;
	int		i;
	int		j;

	mlx_con = mlx_init();
	if (!mlx_con)
		exit_error();
	mlx_win = mlx_new_window(mlx_con, 1000, 1000, "FDF");
	if (!mlx_win)
		exit_error();
	if (map)
	{
		i = -1;
		y = 400;
		while(map[++i])
		{
			j = -1;
			x = 400;
			while(map[i][++j].height <= INT_MAX)
				mlx_pixel_put(mlx_con, mlx_win, ++x, y, map[i][j].color);
			++y;
		}
		
	}
	mlx_loop(mlx_con);
	free(mlx_con);
	free(mlx_win);
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
	free (ch_map);
	fdf(map);
	ft_free_matrix_tmap(map);
	return (0);
}
