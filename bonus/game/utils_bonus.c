/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:13 by asayad            #+#    #+#             */
/*   Updated: 2025/02/22 19:36:37 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

bool	valid_ray_intersection(t_game *game, float hx, float hy, int ray)
{
	(void)ray;
	float	a[3][2];
	int		j;
	int		x_c;
	int		y_c;

	j = 0;
	a[0][0] = game->pl_y_pix + hy;
	a[0][1] = game->pl_x_pix + hx;
	a[1][0] = game->pl_y_pix + hy + 0.0005f;
	a[1][1] = game->pl_x_pix + hx + 0.0005f;
	a[2][0] = game->pl_y_pix + hy - 0.0005f;
	a[2][1] = game->pl_x_pix + hx - 0.0005f;
	while (j < 3)
	{
		y_c = (int)floor(a[j][0] * REV_TILE);
		x_c = (int)floor(a[j][1] * REV_TILE);
		if (y_c < 0 || y_c >= game->map_inf->map_height || x_c < 0 || x_c
			>= ft_strlen(game->map[y_c]) || game->map[y_c][x_c] == '1')
			return (0);
		if (game->map[y_c][x_c] == 'D')
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

bool	inside_mmap(float x_pix, float y_pix)
{
	if (powf(x_pix - MINI_MAP_RADIUS, 2)
		+ powf(y_pix - MINI_MAP_RADIUS, 2) <= RADIUS_SQUARE)
		return (1);
	return (0);
}
