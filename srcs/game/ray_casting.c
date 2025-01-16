/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:03 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/16 11:43:50 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ray_casting(t_game *game)
{
	int		ray;
	float	max_ang;
    float   alpha;

	ray = 0;
	max_ang = game->pl_inf->rot_angle + deg2rad(FOV / 2.0);
	alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
	normalize_ang(&alpha, &max_ang);
	while (ray < SCREEN_WIDTH) // && game->inter->alpha <= max_ang
	{
		game->rays[ray].horiz = false;
		game->rays[ray].alpha = alpha;
		inter_horizontal(game, ray);
		inter_vertical(game, ray);
		shortest_distance(game, ray);
		// render_ray(game, ray);
		ray++;
		alpha += deg2rad(RAY_ANG);
		if (alpha > 2 * PI)
		{
			alpha -= 2 * PI;
			max_ang -= 2 * PI;
		}
	}
}
