/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:32:49 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/24 13:45:08 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	*get_color(long int height)
{
	const char	*white = "0xFFEEFD";
	const char	*yellow = "0xF1C40F";
	const char	*green = "0x2ECC71";
	const char	*blue = "0x3498DB";
	const char	*purple = "0x9B59B6";

	if (height < 1)
		return ((char *) purple);
	else if (height <= 3)
		return ((char *) blue);
	else if (height <= 5)
		return ((char *) green);
	else if (height <= 10)
		return ((char *) yellow);
	else
		return ((char *) white);
}

long int	gradient_color_hor(long int color0, long int color1, t_coord coord)
{
	float		d;
	long int	red;
	long int	blue;
	long int	green;

	d = (coord.x1 - coord.x0) / (coord.x2 - coord.x0);
	red = ((1.0 - d) * ((color0 >> 16) & 0xFF) + d * ((color1 >> 16) & 0xFF));
	green = ((1.0 - d) * ((color0 >> 8) & 0xFF) + d * ((color1 >> 8) & 0xFF));
	blue = ((1.0 - d) * (color0 & 0xFF) + d * (color1 & 0xFF));
	return ((red << 16) | (green << 8) | blue);
}

long int	gradient_color_ver(long int color0, long int color1, t_coord coord)
{
	float		d;
	long int	red;
	long int	blue;
	long int	green;

	d = (coord.y1 - coord.y0) / (coord.y2 - coord.y0);
	red = ((1.0 - d) * ((color0 >> 16) & 0xFF) + d * ((color1 >> 16) & 0xFF));
	green = ((1.0 - d) * ((color0 >> 8) & 0xFF) + d * ((color1 >> 8) & 0xFF));
	blue = ((1.0 - d) * (color0 & 0xFF) + d * (color1 & 0xFF));
	return ((red << 16) | (green << 8) | blue);
}
