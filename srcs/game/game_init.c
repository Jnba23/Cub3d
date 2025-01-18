/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:41:48 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/18 23:13:45 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	game_struct_init(t_map *map_inf, t_game **game, t_player *pl_inf)
{
	int	i;

	i = 0;
	(*game) = malloc(sizeof(t_game));
	//protect
	(*game)->map = map_inf->map_2d;
	(*game)->map_inf = map_inf;
	(*game)->pl_inf = pl_inf;
	(*game)->pl_inf->pl_x = map_inf->p_pos_x;
	(*game)->pl_inf->pl_y = map_inf->p_pos_y;
	(*game)->pl_inf->pl_dir = map_inf->pl_dir;
	(*game)->pl_inf->walk_dir = 0;
	(*game)->pl_inf->turn_dir = 0;
	(*game)->ray_ang = deg2rad(RAY_ANG);
	(*game)->pl_inf->rot_angle = deg2rad(0);
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
	(*game)->rays = malloc(sizeof(t_ray) * SCREEN_WIDTH);
	//protect
	while (i < SCREEN_WIDTH)
	{
		(*game)->rays[i].x = 0.0;
		(*game)->rays[i].y = 0.0;
		(*game)->rays[i].horiz = false;
		(*game)->rays[i].ray_lenght = 0.0;
		(*game)->rays[i].d = 0;
		i++;
	}
}

void	window_init(t_game *game, t_map *map_inf)
{
	(void)map_inf;
	game->game = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba", 1);
	game->game_img = mlx_new_image(game->game, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mmap_image = mlx_new_image(game->game, 2 * MINI_MAP_RADIUS, MINI_MAP_RADIUS);
	mlx_image_to_window(game->game, game->game_img, 0, 0);
}
