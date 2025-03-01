/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:13 by asayad            #+#    #+#             */
/*   Updated: 2025/03/01 13:04:15 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	va_y_up(float va)
{
	if ((va >= 0 && va <= PI))
		return (0);
	return (1);
}

int	va_x_right(float va)
{
	if ((va >= 0 && va <= PI / 2) || (va >= (3 * PI) / 2.0 && va <= 2 * PI))
		return (1);
	return (0);
}

bool	valid_ray_intersection(t_game *game, float hx, float hy)
{
	float	a[3][2];
	int		j;
	int		x_coo;
	int		y_coo;

	j = 0;
	a[0][0] = game->pl_y_pix + hy;
	a[0][1] = game->pl_x_pix + hx;
	a[1][0] = game->pl_y_pix + hy + 0.0004554f;
	a[1][1] = game->pl_x_pix + hx + 0.0004554f;
	a[2][0] = game->pl_y_pix + hy - 0.0004554f;
	a[2][1] = game->pl_x_pix + hx - 0.0004554f;
	while (j < 3)
	{
		y_coo = (int)floor(a[j][0] * game->rev_tile);
		x_coo = (int)floor(a[j][1] * game->rev_tile);
		if (y_coo < 0 || y_coo >= game->map_inf->map_height || x_coo < 0
			|| x_coo >= ft_strlen(game->map[y_coo])
			|| game->map[y_coo][x_coo] == '1')
			return (0);
		j++;
	}
	return (1);
}

void	normalize_ang(float *alpha)
{
	if (*alpha < 0)
		*alpha = fmod(*alpha, 2 * PI) + 2 * PI;
	if (*alpha > 2 * PI)
		*alpha -= 2 * PI;
}
