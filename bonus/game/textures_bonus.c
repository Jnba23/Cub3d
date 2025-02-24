/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:16:00 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/23 20:30:20 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

uint32_t	get_texture_pixel(mlx_image_t *texture, int x, int y)
{
	uint8_t	*pixel;
	size_t	pixel_pos;

	pixel_pos = (y * texture->width + x) * 4;
	pixel = (uint8_t *)&texture->pixels[pixel_pos];
	return ((uint32_t)(pixel[0] << 24)
	| (uint32_t)(pixel[1] << 16)
	| (uint32_t)(pixel[2] << 8)
	| (uint32_t)pixel[3]);
}

double	calculate_wallx(t_game *game, int i)
{
	double	wallx;

	wallx = 0.0;
	if (!game->rays[i].horiz)
		wallx = game->rays[i].x;
	else
		wallx = game->rays[i].y;
	wallx = wallx / TILE_SIZE;
	wallx -= floor(wallx);
	if ((game->rays[i].horiz && game->rays[i].x < game->pl_x_pix)
		|| (!game->rays[i].horiz && game->rays[i].y > game->pl_y_pix))
		wallx = 1.0 - wallx;
	return (wallx);
}

void	calculate_tex_x(t_game *game, mlx_image_t *texture, int i)
{
	game->text->wall_x = calculate_wallx(game, i);
	game->text->tex_x = (int)(game->text->wall_x * texture->width);
	if (game->text->tex_x < 0)
		game->text->tex_x = 0;
	if (game->text->tex_x >= (int)texture->width)
		game->text->tex_x = texture->width - 1;
}

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
	game->text->img_door = mlx_texture_to_image
		(game->game, game->map_inf->door);
	if (!game->text->img_north || !game->text->img_south
		|| !game->text->img_east || !game->text->img_west
		|| !game->text->img_west || !game->text->img_door)
		return (0);
	return (1);
}
