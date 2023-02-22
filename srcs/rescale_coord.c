/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescale_coord.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:46:28 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/21 15:47:15 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_max_x(t_map_proj **map_proj)
{
	int	max;
	int	i;
	int	j;

	max = INT_MIN;
	i = -1;
	while (map_proj[++i])
	{
		j = -1;
		while (map_proj[i][++j].x <= INT_MAX)
		{
			if (map_proj[i][j].x > max)
				max = map_proj[i][j].x;
		}
	}
	return (max);
}

int	get_max_y(t_map_proj **map_proj)
{
	int	max;
	int	i;
	int	j;

	max = INT_MIN;
	i = -1;
	while (map_proj[++i])
	{
		j = -1;
		while (map_proj[i][++j].y <= INT_MAX)
		{
			if (map_proj[i][j].y > max)
				max = map_proj[i][j].y;
		}
	}
	return (max);
}

void	rescale_coords(t_map_proj **map_proj)
{
	t_aux	aux;
	int		map_size;
	int		i;
	int		j;
	float	scale;

	get_max_min(&aux, map_proj);
	map_size = fmax(aux.max_x - aux.min_x, aux.max_y - aux.min_y);
	scale = 950 / (float)map_size;
	if (scale == 0)
		scale = 1;
	i = -1;
	while (map_proj[++i])
	{
		j = -1;
		while (map_proj[i][++j].y <= INT_MAX)
		{
			map_proj[i][j].x = ((map_proj[i][j].x - aux.min_x) * scale) + \
			((1024 - (aux.max_x - aux.min_x) * scale) / 2);
			map_proj[i][j].y = ((map_proj[i][j].y - aux.min_y) * scale) + \
			((1024 - (aux.max_y - aux.min_y) * scale) / 2);
		}
	}
}
