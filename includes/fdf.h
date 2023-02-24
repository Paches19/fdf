/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:54 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/24 13:33:52 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "unistd.h"
# include "mlx.h"
# include "math.h"
# include <stdlib.h>
# include "fcntl.h"
# include "stdio.h"
# include "limits.h"
# include "errno.h"
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

typedef struct s_img
{
	void	*img;
	char	*img_ptr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	long int	height;
	long int	color;
	int			height_scale;
}				t_map;

typedef struct s_map_proj
{
	long int	x;
	long int	y;
}				t_map_proj;

typedef struct s_coord
{
	float	x0;
	float	x1;
	float	y0;
	float	y1;
	float	x2;
	float	y2;
	int		i;
	int		j;
	float	x_inc;
	float	y_inc;
	int		iter;
	int		iter2;
	int		n_col;
	int		n_col2;
}			t_coord;

typedef struct s_aux
{
	int	max_x;
	int	max_y;
	int	min_x;
	int	min_y;
	int	max_abs_x;
	int	max_abs_y;
}		t_aux;

typedef struct s_minilibx
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}			t_minilibx;

typedef struct s_megastruct
{
	t_minilibx	*mlx;
	t_map		**map;
}				t_megastruct;

char		*get_next_line(int fd);
char		*ft_strjoin_gnl(char *line, char **save_read);
char		*ft_memcpy_gnl(char *dst, char *src);
int			ft_strchr_gnl(char *s, int c);
size_t		ft_strlen_gnl(char *s, int gnl);
char		*ft_calloc_gnl(size_t count, size_t size);
char		*write_line(char *line, char **save_read);
char		**ft_split(char *s, char c);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *s);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		draw_horizontal_line(t_map **map, t_coord coord, t_img *img);
void		draw_vertical_line(t_map **map, t_coord coord, t_img *img);
void		calc_horizontal_lines(t_map_proj **map_proj, t_map **map, \
			t_img *img);
void		calc_vertical_lines(t_map_proj **map_proj, t_map **map, t_img *img);
void		check_color(char *color);
void		exit_error_hexa(void);
void		exit_error(void);
void		exit_map_error(void);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long int	ft_htol(char *color, long int height);
size_t		ft_strlen(const char *s);
void		ft_free_matrix_char(char **matrix);
void		ft_free_matrix_tmap(t_map **matrix);
void		ft_free_matrix_tmap_proj(t_map_proj **matrix);
int			get_min_x(t_map_proj **map_proj);
int			get_min_y(t_map_proj **map_proj);
int			get_max_abs_x(t_map_proj **map_proj);
int			get_max_abs_y(t_map_proj **map_proj);
void		get_max_min(t_aux *aux, t_map_proj **map_proj);
int			ft_num_rows(t_map **map);
int			ft_num_cols(t_map *map);
int			ft_size_row(char **row);
int			copy_map(t_map **map, t_map **new_map);
t_map_proj	**project_map(t_map **map, int height_scale);
void		rescale_coords(t_map_proj **map_proj);
char		*read_map(char **argv);
t_map		**build_map(char *ch_map);
char		*create_color(long int height);
int			get_max_y(t_map_proj **map_proj);
int			get_max_x(t_map_proj **map_proj);
t_map		**num_to_map(char **row, t_map **map);
void		init_new_map(t_map **new_map, t_map **map, char **row);
int			key_adjust(int keycode, t_megastruct *megastruct);
int			esc_hook(int keycode, t_minilibx *mlx);
int			ft_close(t_minilibx *mlx);
long int	gradient_color_ver(long int color0, long int color1, t_coord coord);
long int	gradient_color_hor(long int color0, long int color1, t_coord coord);
char		*get_color(long int height);

#endif