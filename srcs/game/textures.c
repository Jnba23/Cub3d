/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:16:00 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/23 18:27:53 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	draw_textured_wall(t_game *game, int i)
{
	mlx_image_t	*texture;
	int			y;
	size_t		pixel_pos;
	uint32_t	color;

	if (!assign_texture(game, i, &texture))
		return (0);
	calculate_tex_x(game, texture, i);
	y = game->rays[i].top_pix;
	while (y < game->rays[i].bott_pix)
	{
		game->text->pos = (y - game->rays[i].top_pix) / game->rays[i].wall_h;
		game->text->tex_y = (int)(game->text->pos * texture->height);
		if (game->text->tex_y >= (int)texture->height)
			game->text->tex_y = (int)(texture->height - 1);
		pixel_pos = (game->text->tex_y
				* texture->width + game->text->tex_x) * 4;
		game->text->pixel = (uint8_t *)&texture->pixels[pixel_pos];
		color = (uint32_t)(game->text->pixel[0] << 24)
			| (uint32_t)(game->text->pixel[1] << 16)
			| (uint32_t)(game->text->pixel[2] << 8) | (uint32_t)game->text->pixel[3];
		mlx_put_pixel(game->game_img, i, y, color);
		y++;
	}
	return (1);
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
