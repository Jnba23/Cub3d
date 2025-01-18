/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:03 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/18 23:39:39 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cast_rays(t_game *game)
{
	int		ray;

	ray = -1;
	game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
	normalize_ang(&game->inter->alpha);
	while (++ray < SCREEN_WIDTH)
	{
		inter_horizontal(game, ray);
		inter_vertical(game, ray);
		shortest_distance(game, ray);
		// render_ray(game, ray);
		game->inter->alpha += game->ray_ang;
		normalize_ang(&game->inter->alpha);
	}
}