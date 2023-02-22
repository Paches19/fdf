/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:38:56 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/22 15:56:23 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	copy_map(t_map **map, t_map **new_map)
{
	int	i;
	int	j;

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
	return (i);
}

void	init_new_map(t_map **new_map, t_map **map, char **row)
{
	int			i;
	int			num_cols;
	const int	new_cols = ft_size_row(row);

	i = -1;
	if (map)
	{
		while (map[++i])
		{
			num_cols = ft_num_cols(map[i]);
			new_map[i] = (t_map *) ft_calloc(sizeof(t_map), num_cols + 1);
			if (!new_map[i])
			{
				ft_free_matrix_tmap(new_map);
				exit_error();
			}
		}
		--i;
	}
	new_map[++i] = (t_map *) ft_calloc(sizeof(t_map), new_cols + 1);
	if (!new_map[i])
	{
		ft_free_matrix_tmap(new_map);
		exit_error();
	}
}

char	*read_map(char **argv)
{
	int			fd;
	char		*buf;
	char		*map;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error();
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

t_map	**build_map(char *ch_map)
{
	int		i;
	t_map	**map;
	char	**matrix_map;
	char	**row;

	matrix_map = ft_split(ch_map, '\n');
	map = NULL;
	i = -1;
	while (matrix_map[++i])
	{
		row = ft_split(matrix_map[i], ' ');
		map = num_to_map(row, map);
		ft_free_matrix_char(row);
	}
	ft_free_matrix_char(matrix_map);
	return (map);
}
