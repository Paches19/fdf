/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:57 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/24 12:06:08 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->img_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	ft_close(t_minilibx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit (0);
	return (0);
}

static int	key_hook(int keycode, t_minilibx *mlx)
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
	megastruct->mlx->img.img_ptr = mlx_get_data_addr(megastruct->mlx->img.img, &megastruct->mlx->img.bpp, \
	&megastruct->mlx->img.line_len, &megastruct->mlx->img.endian);
	map_proj = project_map(megastruct->map, megastruct->map[0]->height_scale);
	rescale_coords(map_proj);
	calc_horizontal_lines(map_proj, megastruct->map, &megastruct->mlx->img);
	calc_vertical_lines(map_proj, megastruct->map, &megastruct->mlx->img);
	mlx_put_image_to_window(megastruct->mlx->mlx, megastruct->mlx->mlx_win, megastruct->mlx->img.img, 0, 0);
	return (0);
}

void init_megastruct(t_map **map, t_minilibx *mlx, t_megastruct *mega_struct)
{
	map[0]->height_scale = 200;
	mega_struct->mlx = mlx;
	mega_struct->map = map;
	mega_struct->map[0]->height_scale = 200;	
}

void	fdf(t_map **map)
{
	t_minilibx		mlx;
	t_map_proj		**map_proj;
	t_megastruct	mega_struct;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		exit_error();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 1024, 1024, "FDF");
	if (!mlx.mlx_win)
		exit_error();
	mlx.img.img = mlx_new_image(mlx.mlx, 1024, 1024);
	mlx.img.img_ptr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, \
	&mlx.img.line_len, &mlx.img.endian);
	init_megastruct(map, &mlx, &mega_struct);
	mlx_hook(mlx.mlx_win, 2, 0, key_adjust, &mega_struct);
	map_proj = project_map(map, map[0]->height_scale);
	rescale_coords(map_proj);
	calc_horizontal_lines(map_proj, map, &mlx.img);
	calc_vertical_lines(map_proj, map, &mlx.img);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
	mlx_hook(mlx.mlx_win, 3, 0, key_hook, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, ft_close, &mlx);
	mlx_loop(mlx.mlx);
	return ;
}

void ft_leaks (void)
{
	system("leaks -q fdf");
}

int	main(int argc, char **argv)
{
	t_map	**map;
	char	*ch_map;

	atexit(ft_leaks);
	if (argc != 2)
		return (1);
	ch_map = read_map(argv);
	map = build_map(ch_map);
	free(ch_map);
	while (1)
		fdf(map);
	ft_free_matrix_tmap(map);
	return (0);
}
