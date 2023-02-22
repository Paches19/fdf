/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max_min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:43:48 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/21 15:44:32 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_min_x(t_map_proj **map_proj)
{
	int	min;
	int	i;
	int	j;

	min = INT_MAX;
	i = -1;
	while (map_proj[++i])
	{
		j = -1;
		while (map_proj[i][++j].x <= INT_MAX)
		{
			if (map_proj[i][j].x < min)
				min = map_proj[i][j].x;
		}
	}
	return (min);
}

int	get_min_y(t_map_proj **map_proj)
{
	int	min;
	int	i;
	int	j;

	min = INT_MAX;
	i = -1;
	while (map_proj[++i])
	{
		j = -1;
		while (map_proj[i][++j].y <= INT_MAX)
		{
			if (map_proj[i][j].y < min)
				min = map_proj[i][j].y;
		}
	}
	return (min);
}

int	get_max_abs_x(t_map_proj **map_proj)
{
	int	max;
	int	i;
	int	j;

	max = INT_MIN;
	i = -1;
	while (map_proj[++i])
	{
		j = -1;
		while (labs(map_proj[i][++j].x) <= INT_MAX)
		{
			if (labs(map_proj[i][j].x) > max)
				max = labs(map_proj[i][j].x);
		}
	}
	return (max);
}

int	get_max_abs_y(t_map_proj **map_proj)
{
	int	max;
	int	i;
	int	j;

	max = INT_MIN;
	i = -1;
	while (map_proj[++i])
	{
		j = -1;
		while (labs(map_proj[i][++j].y) <= INT_MAX)
		{
			if (labs(map_proj[i][j].y) > max)
				max = labs(map_proj[i][j].y);
		}
	}
	return (max);
}

void	get_max_min(t_aux *aux, t_map_proj **map_proj)
{
	aux->max_x = get_max_x(map_proj);
	aux->max_y = get_max_y(map_proj);
	aux->min_x = get_min_x(map_proj);
	aux->min_y = get_min_y(map_proj);
	aux->max_abs_x = get_max_abs_x(map_proj);
	aux->max_abs_y = get_max_abs_y(map_proj);
}
