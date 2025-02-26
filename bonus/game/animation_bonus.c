/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:40:24 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/23 17:12:21 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	delete_text(int i, t_game *game)
{
	int	j;

	j = 0;
	while (j < i)
	{
		mlx_delete_image(game->game, game->img[j]);
		j++;
	}
	free(game->img);
}

static int	load_torch_textures(t_game *game, char *paths[], int num_frames)
{
	int				i;
	mlx_texture_t	*texture;

	i = 0;
	while (i < num_frames)
	{
		texture = mlx_load_png(paths[i]);
		if (!texture)
		{
			delete_text(i, game);
			return (0);
		}
		game->img[i] = mlx_texture_to_image(game->game, texture);
		if (!game->img[i])
		{
			mlx_delete_texture(texture);
			delete_text(i, game);
			return (0);
		}
		mlx_delete_texture(texture);
		mlx_image_to_window(game->game, game->img[i], 600, 900);
		game->img[i]->enabled = (i == 0);
		i++;
	}
	return (1);
}

void	init_torch_animation(t_game *game)
{
	int		num_frames;
	char	*paths[11];

	num_frames = 11;
	game->img = malloc(sizeof(mlx_image_t *) * num_frames);
	if (!game->img)
		return ;
	game->torch_frame = 0;
	paths[0] = "./torch/1.png";
	paths[1] = "./torch/3.png";
	paths[2] = "./torch/4.png";
	paths[3] = "./torch/5.png";
	paths[4] = "./torch/6.png";
	paths[5] = "./torch/8.png";
	paths[6] = "./torch/9.png";
	paths[7] = "./torch/10.png";
	paths[8] = "./torch/11.png";
	paths[9] = "./torch/12.png";
	paths[10] = "./torch/13.png";
	if (!load_torch_textures(game, paths, num_frames))
		return ;
}

void	animate_torch(void *param)
{
	static int	frame_counter;
	t_game		*game;
	int			animation_speed;

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
