/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:40:22 by hmoukit           #+#    #+#             */
/*   Updated: 2025/03/01 13:39:24 by asayad           ###   ########.fr       */
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
		coo.x1 = (int)(cos(start_ang) * 15) + game->mmap_radius;
		coo.y1 = (int)(sin(start_ang) * 15) + game->mmap_radius;
		render_ray(game, &coo);
		start_ang += game->ray_ang;
	}
}
