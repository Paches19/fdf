/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:13 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/21 15:37:31 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_color(char *color)
{
	int	i;

	if (!color)
		return ;
	if (color[0] != '0' || color[1] != 'x')
		exit_error_hexa();
	i = 1;
	while (color[++i])
	{
		if (color[i] < '0' || (color[i] > '9' && color[i] < 'A'))
			exit_error_hexa();
		if ((color[i] > 'F' && color[i] < 'a') || color[i] > 'f')
			exit_error_hexa();
	}	
}

void	exit_error_hexa(void)
{
	int	err;

	err = errno;
	perror("Codigo de color introducido no válido\n");
	perror("El formato para una altura con color es:\n");
	perror("altura,codigo -> 0,0xFFFFFF\n");
	exit(err);
}

void	exit_error(void)
{
	int	err;

	err = errno;
	perror(strerror(err));
	exit(err);
}

void	exit_map_error(void)
{
	write(1, "Mapa incorrecto, debe tener el mismo numero de columnas en \
	en todas las filas\n", 79);
	exit(1);
}
