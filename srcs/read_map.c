/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:38:56 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/24 16:46:03 by adpachec         ###   ########.fr       */
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

// void	init_new_map(t_map **new_map, t_map **map, char **row)
// {
// 	int			i;
// 	int			num_cols;
// 	const int	new_cols = ft_size_row(row);

// 	i = -1;
// 	if (map)
// 	{
// 		while (map[++i])
// 		{
// 			num_cols = ft_num_cols(map[i]);
// 			new_map[i] = (t_map *) ft_calloc(sizeof(t_map), num_cols + 1);
// 			if (!new_map[i])
// 			{
// 				ft_free_matrix_tmap(new_map);
// 				exit_error();
// 			}
// 		}
// 		--i;
// 	}
// 	new_map[++i] = (t_map *) ft_calloc(sizeof(t_map), new_cols + 1);
// 	if (!new_map[i])
// 	{
// 		ft_free_matrix_tmap(new_map);
// 		exit_error();
// 	}
// }

t_map_size	size_map(char **argv)
{
	int			fd;
	t_map_size	map_size;
	char		*buf;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error();
	buf = get_next_line(fd);
	if (!buf)
		exit(0);
	map_size.n_rows = 1;
	map_size.n_cols = ft_words(buf, ' ');
	while (buf != NULL)
	{
		free(buf);
		buf = get_next_line(fd);
		if (buf && ft_words(buf, ' ') != (unsigned long) map_size.n_cols)
		{
			free(buf);
			exit (0);
		}
		++map_size.n_rows;
	}
	close(fd);
	return (map_size);
}

// char	*read_map(char **argv)
// {
// 	int			fd;
// 	char		*buf;
// 	char		*map;

	
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		exit_error();
// 	map = NULL;
// 	buf = NULL;
// 	while (buf || map == NULL)
// 	{
// 		buf = get_next_line(fd);
// 		map = ft_strjoin(map, buf);
// 	}
// 	close(fd);
// 	return (map);
// }

t_map	**init_fast_map(t_map_size map_size)
{
	int		i;
	t_map	**new_map;

	new_map = (t_map **) ft_calloc(sizeof(t_map *), map_size.n_rows);
	if (!new_map)
		exit (1);
	i = -1;
	while (++i < map_size.n_rows - 1)
	{
		new_map[i] = (t_map *) ft_calloc(sizeof(t_map), (map_size.n_cols + 1));
		if (!new_map[i])
		{
			ft_free_matrix_tmap(new_map);
			exit (1);
		}	
	}
	return (new_map);
}

void	get_num_color(char **row, t_map ***map, int i)
{
	int		j;
	char	**height_color;

	if (!row)
		return ;
	j = -1;
	while (row[++j])
	{
		height_color = ft_split(row[j], ',');
		(*map)[i][j].height = (long) ft_atoi(height_color[0]);
		(*map)[i][j].color = (long) ft_htol(height_color[1], \
		(*map)[i][j].height);
		ft_free_matrix_char(height_color);
	}
	map[0][i][j].height = (long) INT_MAX + 1;
	map[0][i][j].color = (long) INT_MAX + 1;
}

t_map	**build_map_2(char **argv, t_map_size *map_size)
{
	t_coord		coord;
	int			fd;
	t_map		**map;
	char		**row;

	*map_size = size_map(argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_error();
	map = init_fast_map(map_size[0]);
	coord.i = -1;
	row = NULL;
	while (row || coord.i++ == -1)
	{
		row = ft_split(get_next_line(fd), ' ');
		get_num_color(row, &map, coord.i);
		if (row)
			ft_free_matrix_char(row);
	}
	int i = -1;
	while (map[++i])
	{
		int j = -1;
		while (++j < map_size->n_cols)
			printf("%ld ", map[i][j].height);
		printf("\n");
	}
	printf("\n");printf("\n");
	//exit (0);
	return (map);
}

// t_map	**build_map(char *ch_map)
// {
// 	int		i;
// 	t_map	**map;
// 	char	**matrix_map;
// 	char	**row;

// 	matrix_map = ft_split(ch_map, '\n');
// 	map = NULL;
// 	i = -1;
// 	while (matrix_map[++i])
// 	{
// 		row = ft_split(matrix_map[i], ' ');
// 		map = num_to_map(row, map);
// 		ft_free_matrix_char(row);
// 	}
// 	ft_free_matrix_char(matrix_map);
// 	return (map);
// }
