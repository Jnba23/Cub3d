/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:42:21 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/19 18:08:33 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	update_map_on_move(t_game *game)
{
	if (game->inside_door)
	{
		game->map[game->pl_inf->pl_y][game->pl_inf->pl_x] = 'D';
		game->inside_door = 0;
	}
	else
		game->map[(int)game->pl_inf->pl_y][(int)game->pl_inf->pl_x] = '0';
	if (game->map[(int)(game->pl_y_pix / TILE_SIZE)][(int)(game->pl_x_pix
		/ TILE_SIZE)] == 'D')
	{
		game->inside_door = 1;
		game->map[(int)(game->pl_y_pix / TILE_SIZE)][(int)(game->pl_x_pix
				/ TILE_SIZE)] = '0';
	}
	game->pl_inf->pl_x = game->pl_x_pix / TILE_SIZE;
	game->pl_inf->pl_y = game->pl_y_pix / TILE_SIZE;
	game->map[(int)(game->pl_y_pix / TILE_SIZE)][(int)(game->pl_x_pix
			/ TILE_SIZE)] = game->pl_inf->pl_dir;
}

void	update_map_u_d(t_game *game)
{
	float	x;
	float	y;
	float	p_step;

	p_step = game->pl_inf->walk_dir * PLYR_SPEED;
	x = p_step * cos(game->pl_inf->rot_angle);
	y = p_step * sin(game->pl_inf->rot_angle);
	if (can_move(x, y, game))
	{
		game->pl_y_pix += y;
		game->pl_x_pix += x;
		if (game->pl_x_pix / TILE_SIZE != game->pl_inf->pl_x
			|| game->pl_y_pix / TILE_SIZE != game->pl_inf->pl_y)
			update_map_on_move(game);
	}
}

void	update_map_l_r(t_game *game)
{
	float	x;
	float	y;
	float	p_step;

	p_step = game->pl_inf->turn_dir * PLYR_SPEED;
	if (game->pl_inf->rot_angle < 0)
		game->pl_inf->rot_angle = fmod(game->pl_inf->rot_angle, 2
				* PI) + 2 * PI;
	else if (game->pl_inf->rot_angle > 2 * PI)
		game->pl_inf->rot_angle -= 2 * PI;
	x = p_step * cos(game->pl_inf->rot_angle - (PI / 2));
	y = p_step * sin(game->pl_inf->rot_angle - (PI / 2));
	if (can_move(x, y, game))
	{
		game->pl_y_pix += y;
		game->pl_x_pix += x;
		if (game->pl_x_pix / TILE_SIZE != game->pl_inf->pl_x
			|| game->pl_y_pix / TILE_SIZE != game->pl_inf->pl_y)
			update_map_on_move(game);
	}
}
