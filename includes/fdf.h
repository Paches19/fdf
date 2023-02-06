/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:54 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/06 12:23:59 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "unistd.h"
# include "mlx.h"
# include "math.h"
# include <unistd.h>
# include <stdlib.h>
# include "fcntl.h"
# include "stdio.h"
# include "limits.h"
# include "errno.h"
# include <string.h>
# include <sys/wait.h>

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
}				t_map;

typedef struct s_map_proj
{
	long int	x;
	long int	y;
}				t_map_proj;

typedef struct s_coord
{
	long int	x1;
	long int	y1;
	long int	x2;
	long int	y2;
	int			i;
	int			j;
	float		x_inc;
	float		y_inc;
}				t_coord;

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *line, char **save_read);
char	*ft_memcpy_gnl(char *dst, char *src);
int		ft_strchr_gnl(char *s, int c);
size_t	ft_strlen_gnl(char *s, int gnl);
char	*ft_calloc_gnl(size_t count, size_t size);
char	*write_line(char *line, char **save_read);
char	**ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);

#endif