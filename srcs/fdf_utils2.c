/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:38:04 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/22 16:00:22 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

long int	ft_htol(char *color)
{
	int			i;
	int			base;
	long int	result;
	const char	*white = "0xFFEEFD";

	if (!color)
		color = (char *) white;
	check_color(color);
	i = ft_strlen(color) - 1;
	result = 0;
	base = 1;
	while (i > 1)
	{
		if (ft_isdigit(color[i]))
			result += (color[i] - 48) * base;
		else if (color[i] >= 'a' && color[i] <= 'f')
			result += (color[i] - 87) * base;
		else if (color[i] >= 'A' && color[i] <= 'F')
			result += (color[i] - 55) * base;
		base *= 16;
		--i;
	}
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	ft_free_matrix_char(char **matrix)
{
	size_t	i;

	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_free_matrix_tmap(t_map **matrix)
{
	size_t	i;

	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_free_matrix_tmap_proj(t_map_proj **matrix)
{
	size_t	i;

	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
}
