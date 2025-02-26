/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:48:27 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 18:48:49 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	assign_texture(t_game *game, int i, mlx_image_t **texture)
{
	if (!game->rays[i].horiz && game->rays[i].y > game->pl_y_pix)
		*texture = game->text->img_south;
	else if (!game->rays[i].horiz && game->rays[i].y < game->pl_y_pix)
		*texture = game->text->img_north;
	else if (game->rays[i].horiz && game->rays[i].x > game->pl_x_pix)
		*texture = game->text->img_east;
	else
		*texture = game->text->img_west;
	if (!(*texture) || !(*texture)->pixels)
		return (0);
	return (1);
}

int	init_textures(t_game *game)
{
	game->text->img_north = mlx_texture_to_image
		(game->game, game->map_inf->north);
	game->text->img_south = mlx_texture_to_image
		(game->game, game->map_inf->south);
	game->text->img_east = mlx_texture_to_image
		(game->game, game->map_inf->east);
	game->text->img_west = mlx_texture_to_image
		(game->game, game->map_inf->west);
	if (!game->text->img_north || !game->text->img_south
		|| !game->text->img_east || !game->text->img_west)
		return (0);
	return (1);
}
