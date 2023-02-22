/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:39:57 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/22 19:24:45 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_map_proj	**init_new_map_proj(t_map **map)
{
	t_map_proj	**map_proj;
	const int	num_rows = ft_num_rows(map);
	int			num_cols;
	int			i;

	map_proj = (t_map_proj **) ft_calloc(sizeof(t_map_proj *), num_rows + 1);
	if (!map_proj)
		exit_error();
	i = -1;
	while (map[++i])
	{
		num_cols = ft_num_cols(map[i]);
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

int	get_max_h(t_map **map)
{
	int	i;
	int	j;
	int	max_height;

	i = -1;
	max_height = INT_MIN;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j].height <= INT_MAX)
		{
			if (map[i][j].height > max_height)
				max_height = map[i][j].height;
		}
	}
	if (max_height > 20)
		return (8);
	else if (max_height > 5)
		return (6);
	return (4);
}

int	key_adjust(int keycode, void *height_scale)
{
	int *var = (int *) height_scale;

	// if (keycode == 0x1e)
	keycode = 0;
		*var += 10;
	// else if (keycode == 0x1b)
	// 	*var -= 10;
	printf("hs2: %d", *var);
	return (0);
}

t_map_proj	**project_map(t_map **map, t_minilibx *mlx)
{
	t_map_proj	**map_p;
	t_coord		c;
	const int	scale = 300;
	int			num_cols;
	int			height_scale;

	height_scale = 500;
	mlx_key_hook(mlx->mlx_win, key_adjust, &height_scale);
	printf("hs3: %d", height_scale);
	map_p = init_new_map_proj(map);
	c.i = -1;
	c.y1 = 500 - ((ft_num_rows(map) * scale) / 2);
	while (map[++c.i])
	{
		num_cols = ft_num_cols(map[c.i]);
		c.j = -1;
		c.x1 = 500 - ((num_cols * scale) / 2);
		while (map[c.i][++c.j].height <= INT_MAX)
		{
			map_p[c.i][c.j].x = (c.x1 - c.y1) * sqrt(3 / 2);
			map_p[c.i][c.j].y = ((c.x1 + c.y1) * 0.5) - (height_scale * \
			map[c.i][c.j].height);
			c.x1 += scale;
		}
		c.y1 += scale;
		map_p[c.i][c.j].x = (long int) INT_MAX + 1;
		map_p[c.i][c.j].y = (long int) INT_MAX + 1;
	}
	return (map_p);
}

void	get_num_color(char **row, t_map **map, t_map **new_map)
{
	int			i;
	int			j;
	char		**height_color;

	i = copy_map(map, new_map);
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

	new_map = (t_map **) malloc(sizeof(t_map *) * (num_rows + 1 + 1));
	new_map[num_rows + 1] = NULL;
	if (!new_map)
		exit_error();
	init_new_map(new_map, map, row);
	get_num_color(row, map, new_map);
	ft_free_matrix_tmap(map);
	return (new_map);
}
