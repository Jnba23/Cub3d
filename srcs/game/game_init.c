/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:41:48 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/24 09:47:50 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	game_struct_init(t_map *map_inf, t_game *game, t_player *pl_inf)
{
	game->map = map_inf->map_2d;
	game->map_inf = map_inf;
	game->pl_inf = pl_inf;
	game->pl_inf->pl_x = map_inf->p_pos_x;
	game->pl_inf->pl_y = map_inf->p_pos_y;
	game->pl_inf->pl_dir = map_inf->pl_dir;
	game->pl_inf->walk_dir = 0;
	game->pl_inf->turn_dir = 0;
	game->pl_inf->rot_angle = 0; // remember to return it to the ORIGINS 
	game->pl_inf->rot_speed = deg2rad(1);
	game->map_pix_h = TILE_SIZE * game->map_inf->map_height;
	game->map_pix_w = TILE_SIZE * game->map_inf->map_width;
	game->pl_x_pix = game->pl_inf->pl_x * TILE_SIZE + TILE_SIZE / 2;
	game->pl_y_pix = game->pl_inf->pl_y * TILE_SIZE + TILE_SIZE / 2;
	game->inter = malloc(sizeof(t_inter));
	// game->inter->ray_num = SCREEN_WIDTH / RAY_ANG;
	game->inter->hx = 0.0;
	game->inter->hy = 0.0;
	game->inter->vx = 0.0;
	game->inter->vy = 0.0;
}

void	window_init(t_game *game, t_map *map_inf)
{
	(void)map_inf;
	game->game = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba", 1);
	game->game_win = mlx_new_image(game->game, SCREEN_WIDTH, SCREEN_HEIGHT);
	// game->mmp_win = mlx_new_image(game->game, MINI_MAP_RADIUS * 2, MINI_MAP_RADIUS * 2);
	mlx_image_to_window(game->game, game->game_win, 0, 0);
	// mlx_image_to_window(game->game, game->mmp_win, 0, 0);
}

