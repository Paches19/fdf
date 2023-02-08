/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:57 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/08 11:50:17 by adpachec         ###   ########.fr       */
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

void	ft_free_matrix_tmap_proj(t_map_proj **matrix)
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
	int		sign;
	long	result;

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
	free(s1);
	free (s2);
	return (str);
}

char	*read_map(char **argv)
{
	int			fd;
	char		*buf;
	char		*map;

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

int	ft_num_rows(t_map **map)
{
	int	num_rows;
	int	i;

	num_rows = 0;
	if (!map || !map[0])
		return (0);
	i = -1;
	while (map[++i])
		++num_rows;
	return (num_rows);
}

int	ft_num_cols(t_map **map)
{
	int	num_cols;
	int	i;

	num_cols = 0;
	if (!map || !map[0])
		return (0);
	i = -1;
	while (map[0][++i].height <= INT_MAX)
		++num_cols;
	return (num_cols);
}

int	ft_size_row(char **row)
{
	int	i;
	int	size_row;

	size_row = 0;
	if (!row || !row[0])
		return (size_row);
	i = -1;
	while (row[++i])
		++size_row;
	return (size_row);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->img_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_new_map(t_map **new_map, t_map **map, char **row)
{
	int			i;
	const int	num_cols = ft_size_row(row);

	i = -1;
	if (map)
	{
		while (map[++i])
		{
			new_map[i] = (t_map *) ft_calloc(sizeof(t_map) , num_cols + 1);
			if (!new_map[i])
			{
				ft_free_matrix_tmap(new_map);
				exit_error();
			}
		}
		--i;
	}
	new_map[++i] = (t_map *) ft_calloc(sizeof(t_map), num_cols + 1);
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
	const int	num_rows = ft_num_rows(map);
	//const int	size_row = ft_size_row(row);

	new_map = (t_map **) malloc(sizeof(t_map *) * (num_rows + 1 + 1));
	new_map[num_rows + 1] = NULL;
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
	//int		j;
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
	// i = -1;
	// while (map[++i])
	// {
	// 	j = -1;
	// 	while (map[i][++j].height <= INT_MAX)
	// 		printf("%lu ", map[i][j].height);
	// 	printf("\n");
	// }
	// i = -1;
	// while (map[++i])
	// {
	// 	int r = j;
	// 	j = -1;
	// 	while (++j < r)
	// 		printf("%lu ", map[i][j].color);
	// 	printf("\n");
	// }
	ft_free_matrix_char(matrix_map);
	return (map);
}

t_map_proj	**init_new_map_proj(t_map **map)
{
	t_map_proj	**map_proj;
	const int	num_rows = ft_num_rows(map);
	const int	num_cols = ft_num_cols(map);
	int			i;

	map_proj = (t_map_proj **) ft_calloc(sizeof(t_map_proj *), num_rows + 1);
	if (!map_proj)
		exit_error();
	i = -1;
	while (map[++i])
	{
		map_proj[i] = (t_map_proj *) ft_calloc(sizeof(t_map_proj), \
		num_cols + 1);
		if (!map_proj[i])
		{
			ft_free_matrix_tmap_proj(map_proj);
			exit_error();
		}
	}
	return (map_proj);
}

t_map_proj	**project_map(t_map **map)
{
	t_map_proj	**map_proj;
	int			i;
	int			j;
	int			scale;
	int			x;
	int			y;
	const int	num_rows = ft_num_rows(map);
	const int	num_cols = ft_num_cols(map);

	scale = 50;
	map_proj = init_new_map_proj(map);
	i = -1;
	// x = (num_rows * scale) / 2;
	// y = (num_cols * scale) / 2;
	// x = 500 - x;
	// y = 500 - y;
	// y = 0;
	// while (map[++i])
	// {
	// 	j = -1;
	// 	x = j;
	// 	while (map[i][++j].height <= INT_MAX)
	// 	{
	// 		map_proj[i][j].x = (x - y) * cos(0.523599);
	// 		map_proj[i][j].y = ((x + y) * sin(0.523599)) - (map[i][j].height);
	// 		x += scale;
	// 	}
	// 	y = scale + i;
	// 	map_proj[i][j].x = (long int) INT_MAX + 1;
	// 	map_proj[i][j].y = (long int) INT_MAX + 1;
	// }
	// while (map[++i])
	// {
	// 	j = -1;
	// 	while (map[i][++j].height <= INT_MAX)
	// 	{
	// 		map_proj[i][j].x = (i - j + scale) * cos(0.523599);
	// 		map_proj[i][j].y = ((i + j + scale) * sin(0.523599)) - (map[i][j].height);
	// 		//x += scale;
	// 	}
	// 	//y += scale;
	// 	map_proj[i][j].x = (long int) INT_MAX + 1;
	// 	map_proj[i][j].y = (long int) INT_MAX + 1;
	// }
	y = 0;
	while (map[++i])
	{
		j = -1;
		x = 0;
		while (map[i][++j].height <= INT_MAX)
		{
			map_proj[i][j].x = (x - y) * cos(0.523599);
			map_proj[i][j].y = ((x + y) * sin(0.523599)) - \
			((map[i][j].height) * scale / 1.5);
			x += scale;
		}
		y += scale;
		map_proj[i][j].x = (long int) INT_MAX + 1;
		map_proj[i][j].y = (long int) INT_MAX + 1;
	}
	// i = -1;
	// while (map_proj[++i])
	// {
	// 	j = -1;
	// 	while (map_proj[i][++j].x <= INT_MAX)
	// 	{
	// 		printf("%ld ", map_proj[i][j].x);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// printf("\n");
	// printf("\n");
	// printf("\n");
	/*i = -1;
	while (map_proj[++i])
	{
		j = -1;
		while (map_proj[i][++j].y <= INT_MAX)
		{
			printf("%ld ", map_proj[i][j].y);
		}
		printf("\n");
	}*/
	//exit(1);
	return (map_proj);
}

void	calc_incr_step(t_coord *coord)
{
	int		dx;
	int		dy;
	float	step;
	
	dx = coord->x2 - coord->x1;
	dy = coord->y2 - coord->y1;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	coord->x_inc = dx / step;
	coord->y_inc = dy / step;
}

void	draw_horizontal_line(t_map **map, t_coord coord, t_img *img)
{
	calc_incr_step(&coord);
	while (coord.x1 < coord.x2)
	{
		coord.x1 += coord.x_inc;
		coord.y1 += coord.y_inc;
		my_mlx_pixel_put(img, coord.x1, coord.y1, map[coord.i][coord.j].color);
	}
}

void	draw_vertical_line(t_map **map, t_coord coord, t_img *img)
{
	calc_incr_step(&coord);
	if (coord.y2 > coord.y1)
	{
		while (coord.y1 < coord.y2)
		{
			coord.x1 += coord.x_inc;
			coord.y1 += coord.y_inc;
			printf("i: %d", coord.i);
			printf("j: %d", coord.j);
			my_mlx_pixel_put(img, coord.x1, coord.y1, map[coord.i][coord.j].color);
		}
	}
	else
	{
		while (coord.y1 > coord.y2)
		{
			coord.x1 += coord.x_inc;
			coord.y1 += coord.y_inc;
			printf("i: %d", coord.i);
			printf("j: %d", coord.j);
			my_mlx_pixel_put(img, coord.x1, coord.y1, map[coord.i][coord.j].color);
		}
	}
}

void	calc_horizontal_lines(t_map_proj **map_proj, t_map **map, t_img *img)
{
	t_coord	coord;

	coord.i = -1;
	while (map_proj[++coord.i + 1])
	{
		coord.j = -1;
		while (map_proj[coord.i][++coord.j].x <= INT_MAX && \
		map_proj[coord.i][coord.j + 1].x <= INT_MAX)
		{
			coord.x1 = map_proj[coord.i][coord.j].x;
			coord.x2 = map_proj[coord.i][coord.j + 1].x;
			coord.y1 = map_proj[coord.i][coord.j].y;
			coord.y2 = map_proj[coord.i][coord.j + 1].y;
			draw_horizontal_line(map, coord, img);
		}
	}
}

void	calc_vertical_lines(t_map_proj **map_proj, t_map **map, t_img *img)
{
	t_coord			coord;
	const int		n_col = ft_num_cols(map);
	const int		n_row = ft_num_rows(map);
	int				iter;

	coord.i = -1;
	while (++coord.i < n_row - 1)
	{
		coord.j = -1;
		iter = -1;
		while (map_proj[coord.i][++coord.j].x <= INT_MAX && ++iter < n_col)
		{
			coord.x1 = map_proj[coord.i][coord.j].x;
			coord.x2 = map_proj[coord.i + 1][coord.j].x;
			coord.y1 = map_proj[coord.i][coord.j].y;
			coord.y2 = map_proj[coord.i + 1][coord.j].y;
			printf("i: %d", coord.i);
			printf("j: %d", coord.j);
			draw_vertical_line(map, coord, img);
		}
	}
}

void	fdf(t_map **map)
{
	//void	*mlx_con;
	//void	*mlx_win;
	t_map_proj	**map_proj;
	t_img		img;
	// int		x;
	// int		y;
	int		i;
	int		j;

	/*mlx_con = mlx_init();
	if (!mlx_con)
		exit_error();
	mlx_win = mlx_new_window(mlx_con, 1000, 1000, "FDF");
	if (!mlx_win)
		exit_error();
	img.img = mlx_new_image(mlx_con, 1000, 1000);
	img.img_ptr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, \
	&img.endian);*/
	map_proj = project_map(map);
	// i = -1;
	// while (map_proj[++i])
	// {
	// 	j = -1;
	// 	while (map_proj[i][++j].x <= INT_MAX)
	// 		printf("%lu ", map_proj[i][j].x);
	// 	printf("\n");
	// }
	/*i = -1;
	while (map_proj[++i])
	{
		j = -1;
		if (map_proj[i][++j].x < 1000 && map_proj[i][j].y < 1000)
			my_mlx_pixel_put(&img, map_proj[i][j].x,map_proj[i][j].y, map[i][j].color);
	}*/
	//calc_horizontal_lines(map_proj, map, &img);
	//calc_vertical_lines(map_proj, map, &img);
	//mlx_put_image_to_window(mlx_con, mlx_win, img.img, 0, 0);
	//if (map)
	//{
	//	i = -1;
	//	y = 400;
	//	while(map[++i])
	//	{
			//j = -1;
	//		x = 400;
			//while(map[i][++j].height <= INT_MAX)
			//	mlx_pixel_put(mlx_con, mlx_win, ++x, y, map[i][j].color);
	//		++y;
		//}
	//}
	//mlx_loop(mlx_con);
	//free(mlx_con);
	//free(mlx_win);
	exit(1);
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
