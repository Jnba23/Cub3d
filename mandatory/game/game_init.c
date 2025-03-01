/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:41:48 by hmoukit           #+#    #+#             */
/*   Updated: 2025/03/01 13:08:18 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	game_struct_init(t_map *map_inf, t_game **game, t_player *pl_inf)
{
	init_game_struct(map_inf, game, pl_inf);
	init_inter_struct(game, map_inf);
	init_rays_struct(game, map_inf);
	(*game)->text = malloc(sizeof(t_texture));
	if (!((*game)->text))
	{
		release_ressources(*game, map_inf, 0);
		free(*game);
		free((*game)->inter);
		free((*game)->rays);
		exit(1);
	}
	(*game)->text->tex_x = 0;
	(*game)->text->tex_y = 0;
	(*game)->text->wall_x = 0.0;
	(*game)->text->pos = 0.0;
	(*game)->text->true_w = 0.0;
	window_init(*game, map_inf);
	init_textures(*game);
}

void	init_game_struct(t_map *map_inf, t_game **game, t_player *pl_inf)
{
	(*game) = malloc(sizeof(t_game));
	if (!(*game))
		release_ressources(*game, map_inf, 1);
	(*game)->map = map_inf->map_2d;
	(*game)->map_inf = map_inf;
	(*game)->pl_inf = pl_inf;
	(*game)->pl_inf->pl_x = map_inf->p_pos_x;
	(*game)->pl_inf->pl_y = map_inf->p_pos_y;
	(*game)->pl_inf->pl_dir = map_inf->pl_dir;
	(*game)->pl_inf->walk_dir = 0;
	(*game)->pl_inf->turn_dir = 0;
	(*game)->ray_ang = deg2rad((float)((float)FOV / (float)SCREEN_WIDTH));
	rot_ang(*game);
	(*game)->map_pix_h = TILE_SIZE * (*game)->map_inf->map_height;
	(*game)->map_pix_w = TILE_SIZE * (*game)->map_inf->map_width;
	(*game)->pl_x_pix = (float)((*game)->pl_inf->pl_x
			* TILE_SIZE + TILE_SIZE / 2);
	(*game)->pl_y_pix = (float)((*game)->pl_inf->pl_y
			* TILE_SIZE + TILE_SIZE / 2);
	(*game)->ang_increment = (float)((float)FOV / (float)SCREEN_WIDTH);
	(*game)->rev_tile = (float)(1.0 / (float)TILE_SIZE);
}

void	init_inter_struct(t_game **game, t_map *map_inf)
{
	(*game)->inter = malloc(sizeof(t_inter));
	if (!((*game)->inter))
	{
		release_ressources(*game, map_inf, 0);
		free(*game);
		exit(1);
	}
	(*game)->inter->hx = 0.0;
	(*game)->inter->hy = 0.0;
	(*game)->inter->vx = 0.0;
	(*game)->inter->vy = 0.0;
	(*game)->render = true;
}

void	init_rays_struct(t_game **game, t_map *map_inf)
{
	int	i;

	i = -1;
	(*game)->rays = malloc(sizeof(t_ray) * SCREEN_WIDTH);
	if (!((*game)->rays))
	{
		release_ressources(*game, map_inf, 0);
		free(*game);
		free((*game)->inter);
		exit(1);
	}
	while (++i < SCREEN_WIDTH)
	{
		(*game)->rays[i].x = 0.0;
		(*game)->rays[i].y = 0.0;
		(*game)->rays[i].horiz = false;
		(*game)->rays[i].ray_lenght = 0.0;
		(*game)->rays[i].d = 0;
	}
}

void	window_init(t_game *game, t_map *map_inf)
{
	game->game = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba", 1);
	game->game_img = mlx_new_image(game->game, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->game || !game->game_img)
		release_ressources(game, map_inf, 1);
	if (mlx_image_to_window(game->game, game->game_img, 0, 0) == -1)
		release_ressources(game, map_inf, 1);
}
