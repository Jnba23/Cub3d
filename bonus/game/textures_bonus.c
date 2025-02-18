/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 10:16:00 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/18 19:33:26 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int draw_texture(t_game *game, int i, char c)
{
	mlx_image_t *texture;

	texture = NULL;
	if (c == 'w')
	{
	    if (!assign_texture(game, i, &texture))
			return (0);
	}
	else if (c == 'd')
		texture = game->text->img_door;
    calculate_tex_x(game, texture, i);
    float true_wall_height = ((float)TILE_SIZE / (float)game->rays[i].d) * 
	((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
    float original_top = SCREEN_HEIGHT / 2 - true_wall_height / 2;
    // float original_bottom = SCREEN_HEIGHT / 2 + true_wall_height / 2;
    int draw_start = game->rays[i].top_pix;
    int draw_end = game->rays[i].bott_pix;
    // const int tex_width = texture->width;
    const int tex_height = texture->height - 1;
    for (int y = draw_start; y < draw_end; y++)
    {
        float normalized_y = (y - original_top) / true_wall_height;
        int tex_y = (int)(normalized_y * texture->height);
        tex_y = (tex_y < 0) ? 0 : tex_y;
        tex_y = (tex_y >= (int)texture->height) ? tex_height : tex_y;
        uint32_t color = get_texture_pixel(texture, game->text->tex_x, tex_y);
        mlx_put_pixel(game->game_img, i, y, color);
    }
    return (1);
}

uint32_t get_texture_pixel(mlx_image_t *texture, int x, int y)
{
    uint8_t *pixel;
    size_t pixel_pos;
	
    pixel_pos = (y * texture->width + x) * 4;
    pixel = (uint8_t *)&texture->pixels[pixel_pos];
    return ((uint32_t)(pixel[0] << 24) | 
	(uint32_t)(pixel[1] << 16) | 
	(uint32_t)(pixel[2] << 8) | 
	(uint32_t)pixel[3]);
}

double calculate_wallx(t_game *game, int i)
{
	double wallx = 0.0;
    
    if (!game->rays[i].horiz)
		wallx = game->rays[i].x;
    else
		wallx = game->rays[i].y;
    wallx = wallx / TILE_SIZE;
    wallx -= floor(wallx);
    if ((game->rays[i].horiz && game->rays[i].x < game->pl_x_pix) ||
		(!game->rays[i].horiz && game->rays[i].y > game->pl_y_pix))
	wallx = 1.0 - wallx;
    return (wallx);
}

void calculate_tex_x(t_game *game, mlx_image_t *texture, int i)
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
		|| !game->text->img_west)
		return (0);
	return (1);
}
