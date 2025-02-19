/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:03 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/19 20:08:41 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	is_door(float x, float y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / (float )TILE_SIZE);
	map_y = (int)(y / (float )TILE_SIZE);
	if (map_x >= 0 && map_y >= 0 && map_x < game->map_inf->map_width
		&& map_y < game->map_inf->map_height)
	{
		if (game->map[map_y][map_x] == 'D')
			return (1);
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
