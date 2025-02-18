/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:40:24 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/11 09:52:36 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// void animate_torch(void *param)
// {
//     t_game *game = (t_game *)param;
//     static int frame_counter = 0;
//     int animation_speed = 10;  // Adjust speed (higher = slower)

//     frame_counter++;
//     if (frame_counter >= animation_speed)
//     {
//         frame_counter = 0;
//         // Disable current frame
//         game->img[game->torch_frame]->enabled = false;
//         // Update the frame index
//         game->torch_frame = (game->torch_frame + 1) % 4;
//         // Enable new frame
//         game->img[game->torch_frame]->enabled = true;
//     }
// }

// void animate_torch(void *param)
// {
//     t_game *game = (t_game *)param;
//     static int frame_counter = 0;
//     int animation_speed = 10; // Adjust speed (higher = slower)

//     frame_counter++;
//     if (frame_counter >= animation_speed)
//     {
//         frame_counter = 0;

//         // Remove the old frame
//         mlx_delete_image(game->game, game->img[game->torch_frame]);

//         // Update the frame index
//         game->torch_frame = (game->torch_frame + 1) % 4;

//         // Re-add the new frame at the same position
//         game->img[game->torch_frame] = mlx_texture_to_image(game->game, mlx_load_png("./torch/1.png"));
//         mlx_image_to_window(game->game, game->img[game->torch_frame], 600, 550);
//     }
// 	for (int i = 0; i < 4; i++)
// 	{
// 		char path[50];
// 		sprintf(path, "./torch/%d.png", i + 1);
// 		mlx_texture_t *texture = mlx_load_png(path);
// 		if (!texture)
// 			return; // Handle error
// 		game->img[i] = mlx_texture_to_image(game->game, texture);
// 		mlx_delete_texture(texture); // Free texture after conversion
// 		// Place the images in the window (all at the same position)
// 		mlx_image_to_window(game->game, game->img[i], 200, 300);
// 		game->img[i]->enabled = (i == 0); // Only show the first frame initially
// 	}
// }

