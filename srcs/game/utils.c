/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:13 by asayad            #+#    #+#             */
/*   Updated: 2025/01/14 19:19:15 by asayad           ###   ########.fr       */
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

bool valid_ray_intersection(t_game *game, float hx, float hy)
{
	// float 	a[1][2];
	// int 	j;
	int		x_coo;
	int		y_coo;

	// a[0][0] = game->pl_y_pix + hy;
	// a[0][1] = game->pl_x_pix + hx;
	// a[2][0] = game->pl_y_pix + hy - 5.0f;
	// a[2][1] = game->pl_x_pix + hx;
	// a[3][0] = game->pl_y_pix + hy;
	// a[3][1] = game->pl_x_pix + hx - 5.0f;
	// a[4][0] = game->pl_y_pix + hy;
	// a[4][1] = game->pl_x_pix + hx + 5.0f;
	// while (j < 1)
	// {
		y_coo = (int)floor((game->pl_y_pix + hy) * REV_TILE);
		x_coo = (int)floor((game->pl_x_pix + hx) * REV_TILE);
		if (y_coo < 0 || y_coo >= game->map_inf->map_height || x_coo < 0
			|| x_coo >= ft_strlen(game->map[y_coo]) || game->map[y_coo][x_coo] == '1')
			return (0);
	// 	j++;
	// }
	return (1);
}

void	normalize_ang(float *alpha, float *max_ang)
{
	// if (*alpha != 0 && *alpha != PI / 2 && *alpha != PI
	// 	&& *alpha != 3 * PI / 2)
	// {
		if (*alpha < 0)
		{
			*alpha = fmod(*alpha, 2 * PI) + 2 * PI;
			*max_ang += 2 * PI;
		}
		else if (*alpha > 2 * PI)
			*alpha -= 2 * PI;
	// }
}

// void	reset_mvs_indic(t_game *game)
// {
// 	game->pl_inf->turn_dir = 0;
// 	game->pl_inf->walk_dir = 0;
// 	game->pl_inf->turn_dir = 0;
// }
