/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:15:33 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/24 12:19:37 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_close(t_minilibx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit (0);
	return (0);
}

int	esc_hook(int keycode, t_minilibx *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx, mlx->img.img);
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		exit(0);
	}
	return (0);
}

int	key_adjust(int keycode, t_megastruct *megastruct)
{
	t_map_proj	**map_proj;

	mlx_destroy_image(megastruct->mlx->mlx, megastruct->mlx->img.img);
	if (keycode == 0x7e)
		megastruct->map[0]->height_scale += 200;
	else if (keycode == 0x7d)
		megastruct->map[0]->height_scale -= 200;
	megastruct->mlx->img.img = mlx_new_image(megastruct->mlx->mlx, 1024, 1024);
	megastruct->mlx->img.img_ptr = mlx_get_data_addr(megastruct->mlx->img.img, \
	&megastruct->mlx->img.bpp, \
	&megastruct->mlx->img.line_len, &megastruct->mlx->img.endian);
	map_proj = project_map(megastruct->map, megastruct->map[0]->height_scale);
	rescale_coords(map_proj);
	calc_horizontal_lines(map_proj, megastruct->map, &megastruct->mlx->img);
	calc_vertical_lines(map_proj, megastruct->map, &megastruct->mlx->img);
	mlx_put_image_to_window(megastruct->mlx->mlx, megastruct->mlx->mlx_win, \
	megastruct->mlx->img.img, 0, 0);
	return (0);
}
