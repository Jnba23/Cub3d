/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:03 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 14:00:17 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	is_door(float x, float y, t_game *game)
{
	float	a[3][2];
	int		j;
	int		x_coo;
	int		y_coo;

	j = 0;
	a[0][0] = y;
	a[0][1] = x;
	a[1][0] = y + 0.0001f;
	a[1][1] = x + 0.0001f;
	a[2][0] = y - 0.0001f;
	a[2][1] = x - 0.0001f;
	while (j < 3)
	{
		y_coo = (int)floor(a[j][0] / TILE_SIZE);
		x_coo = (int)floor(a[j][1] / TILE_SIZE);
		if (y_coo < 0 || y_coo >= game->map_inf->map_height || x_coo < 0
			|| x_coo >= ft_strlen(game->map[y_coo]))
			return (0);
		if (game->map[y_coo][x_coo] == 'D')
			return (1);
		j++;
	}
	return (0);
}

void	cast_rays(t_game *game)
{
	int	ray;

	game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
	normalize_ang(&game->inter->alpha);
	ray = -1;
	while (++ray < SCREEN_WIDTH)
	{
		game->rays[ray].hit_door = 0;
		inter_horizontal(game, ray);
		inter_vertical(game, ray);
		shortest_distance(game, ray);
		game->inter->alpha += game->ray_ang;
		normalize_ang(&game->inter->alpha);
	}
}
