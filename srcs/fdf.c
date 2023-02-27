/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:57 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/27 19:33:06 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->img_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_megastruct(t_map **map, t_minilibx *mlx, t_megastruct *mega_struct, t_map_size map_size)
{
	map[0]->height_scale = 200;
	mega_struct->mlx = mlx;
	mega_struct->map = map;
	mega_struct->map[0]->height_scale = 200;
	mega_struct->map_size = map_size;
}

void	fdf(t_map **map, t_map_size map_size)
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
	init_megastruct(map, &mlx, &mega_struct, map_size);
	mlx_hook(mlx.mlx_win, 2, 0, key_adjust, &mega_struct);
	map[0]->height_scale = 200;
	map_proj = project_map(map, map[0]->height_scale, map_size);
	rescale_coords(map_proj);
	calc_horizontal_lines(map_proj, map, &mlx.img, map_size);
	calc_vertical_lines(map_proj, map, &mlx.img, map_size);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
	mlx_hook(mlx.mlx_win, 3, 0, esc_hook, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, ft_close, &mlx);
	mlx_loop(mlx.mlx);
	return ;
}

int	main(int argc, char **argv)
{
	t_map		**map;
	t_map_size map_size;
	//char	*ch_map;

	if (argc != 2)
		return (1);
	//ch_map = read_map(argv);
	map = build_map_2(argv, &map_size);
	//build_map(ch_map);
	//free(ch_map);
	fdf(map, map_size);
	ft_free_matrix_tmap(map);
	return (0);
}
