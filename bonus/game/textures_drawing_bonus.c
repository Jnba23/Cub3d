/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_drawing_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:28:27 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 19:41:11 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	draw_texture_range(t_game *game, mlx_image_t *texture, int i)
{
	int			tex_y;
	uint32_t	color;
	int			y;

	y = game->rays[i].top_pix;
	while (y < game->rays[i].bott_pix)
	{
		tex_y = (int)(((y - (SCREEN_HEIGHT / 2 - game->text->true_wall_h / 2))
					/ game->text->true_wall_h) * texture->height);
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		color = get_texture_pixel(texture, game->text->tex_x, tex_y);
		mlx_put_pixel(game->game_img, i, y, color);
		y++;
	}
	return (1);
}

int	draw_texture(t_game *game, int i, char c)
{
	mlx_image_t	*texture;

	texture = NULL;
	if (c == 'w')
	{
		if (!assign_texture(game, i, &texture))
			return (0);
	}
	else if (c == 'd')
		texture = game->text->img_door;
	calculate_tex_x(game, texture, i);
	game->text->true_wall_h = ((float)TILE_SIZE / (float)game->rays[i].d)
		* ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
	if (!draw_texture_range(game, texture, i))
		return (0);
	return (1);
}
