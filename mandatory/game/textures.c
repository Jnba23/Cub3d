/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:16:00 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 18:55:34 by hmoukit          ###   ########.fr       */
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
	game->text->true_w = ((float)TILE_SIZE / (float)game->rays[i].d)
		* ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
	y = game->rays[i].top_pix;
	while (y < game->rays[i].bott_pix)
	{
		game->text->pos = (y - game->rays[i].top_pix) / game->rays[i].wall_h;
		calculate_tex_y(game, texture, y);
		pixel_pos = (game->text->tex_y
				* texture->width + game->text->tex_x) * 4;
		game->text->pixel = (uint8_t *)&texture->pixels[pixel_pos];
		assign_color(&color, game);
		mlx_put_pixel(game->game_img, i, y, color);
		y++;
	}
	return (1);
}

void	calculate_tex_y(t_game *game, mlx_image_t *texture, int y)
{
	game->text->tex_y = (int)(((y - (SCREEN_HEIGHT / 2 - game->text->true_w
						/ 2)) / game->text->true_w) * texture->height);
	if (game->text->tex_y < 0)
		game->text->tex_y = 0;
	if (game->text->tex_y >= (int)texture->height)
		game->text->tex_y = (int)(texture->height - 1);
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
