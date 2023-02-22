/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:57 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/22 19:21:58 by adpachec         ###   ########.fr       */
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

void	fdf(t_map **map)
{
	t_minilibx	mlx;
	t_map_proj	**map_proj;
	t_img		img;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		exit_error();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 1024, 1024, "FDF");
	if (!mlx.mlx_win)
		exit_error();
	img.img = mlx_new_image(mlx.mlx, 1024, 1024);
	img.img_ptr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, \
	&img.endian);
	mlx.img = img;
	map_proj = project_map(map, &mlx);
	rescale_coords(map_proj);
	calc_horizontal_lines(map_proj, map, &img);
	calc_vertical_lines(map_proj, map, &img);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, img.img, 0, 0);
	mlx_hook(mlx.mlx_win, 3, 0, key_hook, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, ft_close, &mlx);
	mlx_loop(mlx.mlx);
	return ;
}

int	main(int argc, char **argv)
{
	t_map	**map;
	char	*ch_map;

	if (argc != 2)
		return (1);
	ch_map = read_map(argv);
	map = build_map(ch_map);
	free(ch_map);
	fdf(map);
	ft_free_matrix_tmap(map);
	return (0);
}
