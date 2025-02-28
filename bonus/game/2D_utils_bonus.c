/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:40:22 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/28 11:40:37 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	draw_player(t_game *game)
{
	float	start_ang;
	float	end_ang;
	t_coor	coo;

	start_ang = game->pl_inf->rot_angle - deg2rad(FOV / 2);
	end_ang = game->pl_inf->rot_angle + deg2rad(FOV / 2);
	coo.x1 = -3;
	while (start_ang <= end_ang)
	{
		coo.x1 = (int)(cos(start_ang) * 15) + MINI_MAP_RADIUS;
		coo.y1 = (int)(sin(start_ang) * 15) + MINI_MAP_RADIUS;
		render_ray(game, &coo);
		start_ang += deg2rad(RAY_ANG);
	}
}
