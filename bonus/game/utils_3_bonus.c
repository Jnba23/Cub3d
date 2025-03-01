/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:39:04 by hmoukit           #+#    #+#             */
/*   Updated: 2025/03/01 13:44:18 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	quit_game(t_game *game)
{
	free_table(game->map_inf->map_2d, game->map_inf->map_size);
	free_textures(game->map_inf);
	delete_images(game);
	delete_text(11, game);
	free(game->inter);
	free(game->rays);
	free(game->text);
	free(game);
	exit(1);
}

void	draw_ceiling_floor(int i, t_game *game, int bott_pix, int top_pix)
{
	int	j;

	j = 0;
	while (j < top_pix)
	{
		mlx_put_pixel(game->game_img, i, j, get_rgba(game->map_inf->red_c,
				game->map_inf->green_c, game->map_inf->blue_c, 255));
		j++;
	}
	j = bott_pix;
	while (j < SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->game_img, i, j, get_rgba(game->map_inf->red_f,
				game->map_inf->green_f, game->map_inf->blue_f, 255));
		j++;
	}
}

void	init_macros(t_game **game)
{
	(*game)->mmap_radius = (float)(SCREEN_WIDTH * 0.08);
	(*game)->mmap_diameter = (*game)->mmap_radius * 2;
	(*game)->ang_increment = (float)((float)FOV / (float)SCREEN_WIDTH);
	(*game)->rev_tile = (float)(1.0 / (float)TILE_SIZE);
}
