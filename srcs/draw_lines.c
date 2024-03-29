/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:45:00 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/24 16:33:09 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	calc_incr_step(t_coord *coord)
{
	float	dx;
	float	dy;
	float	step;

	dx = coord->x2 - coord->x1;
	dy = coord->y2 - coord->y1;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	coord->x_inc = dx / step;
	coord->y_inc = dy / step;
}

void	draw_horizontal_line(t_map **map, t_coord coord, t_img *img)
{
	calc_incr_step(&coord);
	coord.x0 = coord.x1;
	while (coord.x1 < coord.x2)
	{
		coord.x1 += coord.x_inc;
		coord.y1 += coord.y_inc;
		my_mlx_pixel_put(img, coord.x1, coord.y1, gradient_color_hor(\
		map[coord.i][coord.j].color, map[coord.i][coord.j + 1].color, coord));
	}
}

void	draw_vertical_line(t_map **map, t_coord coord, t_img *img)
{
	calc_incr_step(&coord);
	coord.y0 = coord.y1;
	if (coord.y2 > coord.y1)
	{
		while (coord.y1 < coord.y2)
		{
			coord.x1 += coord.x_inc;
			coord.y1 += coord.y_inc;
			my_mlx_pixel_put(img, coord.x1, coord.y1, gradient_color_ver(\
			map[coord.i][coord.j].color, map[coord.i + 1][coord.j].color, \
			coord));
		}
	}
	else
	{
		while (coord.y1 > coord.y2)
		{
			coord.x1 += coord.x_inc;
			coord.y1 += coord.y_inc;
			my_mlx_pixel_put(img, coord.x1, coord.y1, gradient_color_ver(\
			map[coord.i][coord.j].color, map[coord.i + 1][coord.j].color, \
			coord));
		}
	}
}

void	calc_horizontal_lines(t_map_proj **map_proj, t_map **map, t_img *img, \
t_map_size map_size)
{
	t_coord	coord;

	coord.i = -1;
	while (++coord.i < map_size.n_rows - 1)
	{
		coord.j = -1;
		while (++coord.j < map_size.n_cols - 1)
		{
			coord.x1 = map_proj[coord.i][coord.j].x;
			coord.x2 = map_proj[coord.i][coord.j + 1].x;
			coord.y1 = map_proj[coord.i][coord.j].y;
			coord.y2 = map_proj[coord.i][coord.j + 1].y;
			draw_horizontal_line(map, coord, img);
		}
	}
}

void	calc_vertical_lines(t_map_proj **map_proj, t_map **map, t_img *img, \
t_map_size map_size)
{
	t_coord			coord;
	const int		n_row = ft_num_rows(map);

	coord.i = -1;
	while (++coord.i + 1 < n_row)
	{
		coord.j = -1;
		coord.iter = -1;
		coord.iter2 = -1;
		while (map_proj[coord.i + 1][++coord.j].x <= INT_MAX && \
		++coord.iter < map_size.n_cols)
		{
			coord.x1 = map_proj[coord.i][coord.j].x;
			coord.x2 = map_proj[coord.i + 1][coord.j].x;
			coord.y1 = map_proj[coord.i][coord.j].y;
			coord.y2 = map_proj[coord.i + 1][coord.j].y;
			draw_vertical_line(map, coord, img);
		}
	}
	ft_free_matrix_tmap_proj(map_proj);
}
