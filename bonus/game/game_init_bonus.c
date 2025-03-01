/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:41:48 by hmoukit           #+#    #+#             */
/*   Updated: 2025/03/01 13:43:57 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	init_rays(t_game *game)
{
	int	i;

	game->rays = malloc(sizeof(t_ray) * SCREEN_WIDTH);
	if (!game->rays)
		return (0);
	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		game->rays[i].x = 0.0;
		game->rays[i].y = 0.0;
		game->rays[i].horiz = false;
		game->rays[i].ray_lenght = 0.0;
		game->rays[i].d = 0;
		game->rays[i].hit_door = 0;
	}
	return (1);
}

static int	init_player_and_map(t_game *game, t_map *map_inf, t_player *pl_inf)
{
	game->map = map_inf->map_2d;
	game->map_inf = map_inf;
	game->pl_inf = pl_inf;
	game->pl_inf->pl_x = map_inf->p_pos_x;
	game->pl_inf->pl_y = map_inf->p_pos_y;
	game->pl_inf->pl_dir = map_inf->pl_dir;
	game->pl_inf->walk_dir = 0;
	game->pl_inf->turn_dir = 0;
	game->ray_ang = deg2rad((float)((float)FOV / (float)SCREEN_WIDTH));
	game->pl_inf->rot_angle = 3 * (PI) / 2;
	game->map_pix_h = TILE_SIZE * game->map_inf->map_height;
	game->map_pix_w = TILE_SIZE * game->map_inf->map_width;
	game->pl_x_pix = game->pl_inf->pl_x * TILE_SIZE + TILE_SIZE / 2;
	game->pl_y_pix = game->pl_inf->pl_y * TILE_SIZE + TILE_SIZE / 2;
	game->inter = malloc(sizeof(t_inter));
	if (!game->inter)
		return (0);
	game->inter->hx = 0.0;
	game->inter->hy = 0.0;
	game->inter->vx = 0.0;
	game->inter->vy = 0.0;
	game->render = true;
	return (1);
}

static int	init_textures_and_images(t_game *game)
{
	game->text = malloc(sizeof(t_texture));
	if (!game->text)
		return (0);
	game->torch_frame = 0;
	game->inside_door = 0;
	game->text->true_wall_h = 0;
	return (1);
}

int	game_struct_init(t_map *map_inf, t_game **game, t_player *pl_inf)
{
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (0);
	if (!init_player_and_map(*game, map_inf, pl_inf))
	{
		free(*game);
		return (0);
	}
	init_macros(game);
	if (!init_rays(*game))
	{
		free((*game)->inter);
		free(*game);
		return (0);
	}
	if (!init_textures_and_images(*game))
	{
		free((*game)->inter);
		free((*game)->rays);
		free(*game);
		return (0);
	}
	return (1);
}

void	window_init(t_game *game, t_map *map_inf)
{
	(void)map_inf;
	game->game = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba", 1);
	game->game_img = mlx_new_image(game->game,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mmap_image = mlx_new_image(game->game, game->mmap_diameter,
			game->mmap_diameter);
	if (!game->game || !game->game_img || !game->mmap_image)
		quit_game(game);
	if (mlx_image_to_window(game->game, game->game_img, 0, 0) == -1
		|| mlx_image_to_window(game->game, game->mmap_image, 5, 5) == -1)
		quit_game(game);
	if (!init_torch_animation(game))
		quit_game(game);
}
