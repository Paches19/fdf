/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:43:10 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/21 15:43:28 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_num_rows(t_map **map)
{
	int	num_rows;
	int	i;

	num_rows = 0;
	if (!map || !map[0])
		return (0);
	i = -1;
	while (map[++i])
		++num_rows;
	return (num_rows);
}

int	ft_num_cols(t_map *map)
{
	int	num_cols;
	int	i;

	num_cols = 0;
	if (!map)
		return (0);
	i = -1;
	while (map[++i].height <= INT_MAX)
		++num_cols;
	return (num_cols);
}

int	ft_size_row(char **row)
{
	int	i;
	int	size_row;

	size_row = 0;
	if (!row || !row[0])
		return (size_row);
	i = -1;
	while (row[++i])
		++size_row;
	return (size_row);
}
