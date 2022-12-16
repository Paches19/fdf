/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:37:54 by adpachec          #+#    #+#             */
/*   Updated: 2022/12/16 10:50:47 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "unistd.h"
//# include "mlx.h"

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

typedef struct s_map
{
	long			height;
	long int	colour;
}					t_map;

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