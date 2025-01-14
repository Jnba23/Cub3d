/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:41:48 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/12 14:46:37 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	game_struct_init(t_map *map_inf, t_game **game, t_player *pl_inf)
{
	(*game) = malloc(sizeof(t_game));
	(*game)->map = map_inf->map_2d;
	(*game)->map_inf = map_inf;
	(*game)->pl_inf = pl_inf;
	(*game)->pl_inf->pl_x = map_inf->p_pos_x;
	(*game)->pl_inf->pl_y = map_inf->p_pos_y;
	(*game)->pl_inf->pl_dir = map_inf->pl_dir;
	(*game)->pl_inf->walk_dir = 0;
	(*game)->pl_inf->turn_dir = 0;
	(*game)->pl_inf->rot_angle = deg2rad(270);
	(*game)->map_pix_h = TILE_SIZE * (*game)->map_inf->map_height;
	(*game)->map_pix_w = TILE_SIZE * (*game)->map_inf->map_width;
	(*game)->pl_x_pix = (*game)->pl_inf->pl_x * TILE_SIZE + TILE_SIZE / 2;
	(*game)->pl_y_pix = (*game)->pl_inf->pl_y * TILE_SIZE + TILE_SIZE / 2;
	(*game)->inter = malloc(sizeof(t_inter));
	(*game)->inter->hx = 0.0;
	(*game)->inter->hy = 0.0;
	(*game)->inter->vx = 0.0;
	(*game)->inter->vy = 0.0;
	(*game)->render = true;
	(*game)->d = 0;
	// (*game)->wall_h = 0;
}

void	window_init(t_game *game, t_map *map_inf)
{
	(void)map_inf;
	game->game = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba", 1);
	game->game_win = mlx_new_image(game->game, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(game->game, game->game_win, 0, 0);
}

