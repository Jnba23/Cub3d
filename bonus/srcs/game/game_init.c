/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:41:48 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/18 15:42:29 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	game_struct_init(t_map *map_inf, t_game **game, t_player *pl_inf)
{
	int	i;

	i = -1;
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
	(*game)->pl_inf->rot_angle = deg2rad((3 * PI) / 2);
	(*game)->map_pix_h = TILE_SIZE * (*game)->map_inf->map_height;
	(*game)->map_pix_w = TILE_SIZE * (*game)->map_inf->map_width;
	(*game)->pl_x_pix = (*game)->pl_inf->pl_x * TILE_SIZE + TILE_SIZE / 2;
	(*game)->pl_y_pix = (*game)->pl_inf->pl_y * TILE_SIZE + TILE_SIZE / 2;
	(*game)->inter = malloc(sizeof(t_inter));
	(*game)->inter->hx = 0.0;
	(*game)->inter->hy = 0.0;
	(*game)->inter->vx = 0.0;
	(*game)->inter->vy = 0.0;
	(*game)->inter->last_d_x = 0.0;
	(*game)->inter->last_d_y = 0.0;
	(*game)->render = true;
	(*game)->inside_door = 0;
	(*game)->rays = malloc(sizeof(t_ray) * SCREEN_WIDTH);
	//protect
	while (++i < SCREEN_WIDTH)
	{
		(*game)->rays[i].x = 0.0;
		(*game)->rays[i].y = 0.0;
		(*game)->rays[i].horiz = false;
		(*game)->rays[i].ray_lenght = 0.0;
		(*game)->rays[i].d = 0;
		(*game)->rays[i].hit_door = 0;
	}
	(*game)->text = malloc(sizeof(t_texture));
	(*game)->img = malloc(sizeof(mlx_image_t *) * 4);
	if (!(*game)->img)
		return;
	(*game)->torch_frame = 0;
	(*game)->ver = 0;
	(*game)->hor = 0;
}

void init_torch_animation(t_game *game)
{
    int NUM_FRAMES = 3;
   
    game->img = malloc(sizeof(mlx_image_t*) * NUM_FRAMES);
    if (!game->img)
        return;
    game->torch_frame = 0;
    char *paths[] = {
        "./torch/1.png",
        "./torch/2.png",
        "./torch/3.png"
    };
   int i = 0;
    while (i < NUM_FRAMES)
    {
        mlx_texture_t *texture = mlx_load_png(paths[i]);
        if (!texture)
        {
            for (int j = 0; j < i; j++)
                mlx_delete_image(game->game, game->img[j]);
            free(game->img);
            return;
        }
        game->img[i] = mlx_texture_to_image(game->game, texture);
        if (!game->img[i])
        {
            mlx_delete_texture(texture);
            // Clean up previously allocated resources
            for (int j = 0; j < i; j++)
                mlx_delete_image(game->game, game->img[j]);
            free(game->img);
            return;
        }   
        mlx_delete_texture(texture);
        mlx_image_to_window(game->game, game->img[i], 600, 550);
        game->img[i]->enabled = (i == 0);
		i++;
    }
}

// void cleanup_torch_animation(t_game *game)
// {
//     const int NUM_FRAMES = 3;
    
//     if (game->img)
//     {
//         for (int i = 0; i < NUM_FRAMES; i++)
//         {
//             if (game->img[i])
//                 mlx_delete_image(game->game, game->img[i]);
//         }
//         free(game->img);
//         game->img = NULL;
//     }
// }

void animate_torch(void *param)
{
    t_game *game = (t_game *)param;
    static int frame_counter = 0;
    int animation_speed = 7;
    frame_counter++;
    if (frame_counter >= animation_speed)
    {
        frame_counter = 0;
        game->img[game->torch_frame]->enabled = false;
        game->torch_frame = (game->torch_frame + 1) % 3;
        game->img[game->torch_frame]->enabled = true;
    }
}

void	window_init(t_game *game, t_map *map_inf)
{
	game->game = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba", 1);
	game->game_img = mlx_new_image(game->game, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mmap_image = mlx_new_image(game->game, 2 * MINI_MAP_RADIUS, 2 * MINI_MAP_RADIUS);
	if (!game->game || !game->game_img || !game->mmap_image)
	{
		free_table(&map_inf, map_inf->map_size);
		// free_textures(&map_inf);
		delete_images(game);
		exit(1);
	}
	if (mlx_image_to_window(game->game, game->game_img, 0, 0) == -1
		|| mlx_image_to_window(game->game, game->mmap_image, 5, 5) == -1)
	{
		free_table(&map_inf, map_inf->map_size);
		// free_textures(&map_inf);
		delete_images(game);
		exit(1);
	}
	init_torch_animation(game);
}
