/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:39:04 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 20:17:59 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	quit_game(t_game *game)
{
	free_table(game->map_inf->map_2d, game->map_inf->map_size);
	free_textures(game->map_inf);
	if (game->mmap_inf->n)
		mlx_delete_image(game->game, game->mmap_inf->n);
	if (game->text->img_east)
		mlx_delete_image(game->game, game->text->img_east);
	if (game->text->img_west)
		mlx_delete_image(game->game, game->text->img_west);
	if (game->text->img_north)
		mlx_delete_image(game->game, game->text->img_north);
	if (game->text->img_south)
		mlx_delete_image(game->game, game->text->img_south);
	if (game->text->img_door)
		mlx_delete_image(game->game, game->text->img_door);
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
