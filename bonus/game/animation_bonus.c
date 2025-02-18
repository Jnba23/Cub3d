/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:40:24 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/18 19:56:59 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	init_torch_animation(t_game *game)
{
	int				NUM_FRAMES;
	char			*paths[3];
	int				i;
	mlx_texture_t	*texture;

	NUM_FRAMES = 3;
	game->img = malloc(sizeof(mlx_image_t*) * NUM_FRAMES);
	if (!game->img)
		return ;
	game->torch_frame = 0;
	paths[0] = "./torch/1.png";
	paths[1] = "./torch/2.png";
	paths[2] = "./torch/3.png";
	i = 0;
	while (i < NUM_FRAMES)
	{
		texture = mlx_load_png(paths[i]);
		if (!texture)
		{
			for (int j = 0; j < i; j++)
				mlx_delete_image(game->game, game->img[j]);
			free(game->img);
			return ;
		}
		game->img[i] = mlx_texture_to_image(game->game, texture);
		if (!game->img[i])
		{
			mlx_delete_texture(texture);
			for (int j = 0; j < i; j++)
				mlx_delete_image(game->game, game->img[j]);
			free(game->img);
			return ;
		}
		mlx_delete_texture(texture);
		mlx_image_to_window(game->game, game->img[i], 600, 750);
		game->img[i]->enabled = (i == 0);
		i++;
	}
}

void	animate_torch(void *param)
{
    t_game *game;
    static int frame_counter;
    int animation_speed;

	game = (t_game *)param;
	animation_speed = 7;
    frame_counter++;
    if (frame_counter >= animation_speed)
    {
        frame_counter = 0;
        game->img[game->torch_frame]->enabled = false;
        game->torch_frame = (game->torch_frame + 1) % 3;
        game->img[game->torch_frame]->enabled = true;
    }
}
