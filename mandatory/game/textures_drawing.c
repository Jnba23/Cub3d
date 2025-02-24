/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_drawing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:28:27 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/24 11:24:26 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	draw_texture_range(t_game *game, mlx_image_t *texture, int i)
{
	int			tex_y;
	uint32_t	color;
	int			y;

	y = game->rays[i].top_pix;
	printf("y === %d\n", y);
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

int	draw_textured_wall(t_game *game, int i)
{
	mlx_image_t	*texture;
	int			tex_height;

	texture = NULL;
	if (!assign_texture(game, i, &texture))
		return (0);

	calculate_tex_x(game, texture, i);
	game->text->true_wall_h = ((float)TILE_SIZE / (float)game->rays[i].d)
		* ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
	tex_height = texture->height - 1;
	if (!draw_texture_range(game, texture, i))
		return (0);
	return (1);
}
