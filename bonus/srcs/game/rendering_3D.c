/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:20:42 by asayad            #+#    #+#             */
/*   Updated: 2025/02/18 15:20:30 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// int	draw_door(t_game *game, int i)
// {
// 	mlx_image_t	*texture;
// 	int			y;
// 	size_t		pixel_pos;
// 	uint32_t	color;

// 	texture = game->text->img_door;
// 	calculate_tex_x(game, texture, i);
// 	y = game->rays[i].top_pix;
// 	while (y < game->rays[i].bott_pix)
// 	{
// 		game->text->pos = (y - game->rays[i].top_pix) / game->rays[i].wall_h;
// 		game->text->tex_y = (int)(game->text->pos * texture->height);
// 		if (game->text->tex_y >= (int)texture->height)
// 			game->text->tex_y = (int)(texture->height - 1);
// 		pixel_pos = (game->text->tex_y
// 				* texture->width + game->text->tex_x) * 4;
// 		game->text->pixel = (uint8_t *)&texture->pixels[pixel_pos];
// 		color = (uint32_t)(game->text->pixel[0] << 24)
// 			| (uint32_t)(game->text->pixel[1] << 16)
// 			| (uint32_t)(game->text->pixel[2] << 8) | (uint32_t)game->text->pixel[3];
// 		mlx_put_pixel(game->game_img, i, y, color);
// 		y++;
// 	}
// 	return (1);
// }
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
	
    return wallx;
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

int draw_textured_wall(t_game *game, int i)
{
	mlx_image_t *texture;
    if (!assign_texture(game, i, &texture))
	return (0);
	
    calculate_tex_x(game, texture, i);
    
    // Calculate the true wall height before any clamping
    float true_wall_height = ((float)TILE_SIZE / (float)game->rays[i].d) * 
	((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
    
    // Store the original top and bottom positions before clamping
    float original_top = SCREEN_HEIGHT / 2 - true_wall_height / 2;
    float original_bottom = SCREEN_HEIGHT / 2 + true_wall_height / 2;
    
    // Get the actual drawn coordinates (after clamping)
    int draw_start = game->rays[i].top_pix;
    int draw_end = game->rays[i].bott_pix;
    
    const int tex_width = texture->width;
    const int tex_height = texture->height - 1;
    
    for (int y = draw_start; y < draw_end; y++)
    {
		// Calculate texture Y coordinate based on the true wall height
        float normalized_y = (y - original_top) / true_wall_height;
        int tex_y = (int)(normalized_y * texture->height);
        
        // Clamp texture coordinate
        tex_y = (tex_y < 0) ? 0 : tex_y;
        tex_y = (tex_y >= texture->height) ? tex_height : tex_y;
        
        // Get and draw the pixel
        uint32_t color = get_texture_pixel(texture, game->text->tex_x, tex_y);
        mlx_put_pixel(game->game_img, i, y, color);
    }
    return (1);
}

int draw_door(t_game *game, int i)
{
	mlx_image_t *texture;
	texture = game->text->img_door;
		
	calculate_tex_x(game, texture, i);
	
	// Calculate the true wall height before any clamping
	float true_wall_height = ((float)TILE_SIZE / (float)game->rays[i].d) * 
							((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
	
	// Store the original top and bottom positions before clamping
	float original_top = SCREEN_HEIGHT / 2 - true_wall_height / 2;
	float original_bottom = SCREEN_HEIGHT / 2 + true_wall_height / 2;
	
	// Get the actual drawn coordinates (after clamping)
	int draw_start = game->rays[i].top_pix;
	int draw_end = game->rays[i].bott_pix;
	
	const int tex_width = texture->width;
	const int tex_height = texture->height - 1;
	
	for (int y = draw_start; y < draw_end; y++)
	{
		// Calculate texture Y coordinate based on the true wall height
		float normalized_y = (y - original_top) / true_wall_height;
		int tex_y = (int)(normalized_y * texture->height);
		
		// Clamp texture coordinate
		tex_y = (tex_y < 0) ? 0 : tex_y;
		tex_y = (tex_y >= texture->height) ? tex_height : tex_y;
		
		// Get and draw the pixel
		uint32_t color = get_texture_pixel(texture, game->text->tex_x, tex_y);
		mlx_put_pixel(game->game_img, i, y, color);
	}
	return (1);
}
void render_3D_game(t_game *game)
{
    float angle_beta;
    float min_distance = TILE_SIZE * 0.1; // Minimum distance to prevent extreme distortion
    
    int i = -1;
    game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
    normalize_ang(&game->inter->alpha);
    
    while (++i < SCREEN_WIDTH)
    {
        angle_beta = game->inter->alpha - game->pl_inf->rot_angle;
        normalize_ang(&angle_beta);
        game->rays[i].d *= cos(angle_beta);
        if (game->rays[i].d < min_distance)
            game->rays[i].d = min_distance;
        if (!cos(angle_beta) || !game->rays[i].d)
            game->rays[i].d = 1;
        game->rays[i].wall_h = ((float)TILE_SIZE / (float)game->rays[i].d) * 
                              ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
        int wall_center = SCREEN_HEIGHT / 2;
        game->rays[i].top_pix = wall_center - (game->rays[i].wall_h / 2);
        game->rays[i].bott_pix = wall_center + (game->rays[i].wall_h / 2);
        game->rays[i].bott_pix = (game->rays[i].bott_pix > SCREEN_HEIGHT) ? 
                                 SCREEN_HEIGHT : game->rays[i].bott_pix;
        game->rays[i].top_pix = (game->rays[i].top_pix < 0) ? 0 : game->rays[i].top_pix;
        if (game->rays[i].hit_door)
            draw_door(game, i);
        else
        {
            if (!draw_textured_wall(game, i))
                printf("draw_textured_wall returned 0\n");
        }
        draw_ceiling_floor(i, game, game->rays[i].bott_pix, game->rays[i].top_pix);
        game->inter->alpha += game->ray_ang;
        normalize_ang(&game->inter->alpha);
    }
}
// void render_3D_game(t_game *game)
// {
// 	float	angle_beta;
// 	int		i;

// 	i = -1;
// 	game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
// 	normalize_ang(&game->inter->alpha);
// 	while (++i < SCREEN_WIDTH)
// 	{
// 		angle_beta = game->inter->alpha - game->pl_inf->rot_angle;
// 		game->rays[i].d *= cos(angle_beta);
// 		if (!cos(angle_beta) || !game->rays[i].d)
// 		    game->rays[i].d = 1;
// 		game->rays[i].wall_h = ((float)TILE_SIZE / (float)game->rays[i].d) * ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
// 		game->rays[i].bott_pix = SCREEN_HEIGHT / 2 + game->rays[i].wall_h / 2;
// 		if (game->rays[i].bott_pix > SCREEN_HEIGHT)
// 		    game->rays[i].bott_pix = SCREEN_HEIGHT;
// 		game->rays[i].top_pix = SCREEN_HEIGHT / 2 - game->rays[i].wall_h / 2;
// 		if (game->rays[i].top_pix < 0)
// 		    game->rays[i].top_pix = 0;
// 		if (game->rays[i].hit_door)
// 			draw_door(game, i);
// 		else
// 		{
// 			if (!draw_textured_wall(game, i))
// 				printf("draw_textured_wall returned 0\n");
// 		}
// 		draw_ceiling_floor(i, game, game->rays[i].bott_pix, game->rays[i].top_pix);
// 		game->inter->alpha += game->ray_ang;
// 	}
// }

void	draw_ceiling_floor(int i, t_game *game, int bott_pix, int top_pix)
{
	int j;

	j = 0;
	while (j < top_pix)
	{
		mlx_put_pixel(game->game_img, i, j, 0x00008000);
		j++;
	}
	j = bott_pix;
	while (j <  SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->game_img, i, j, 0x8A8A8AFF);
		j++;
	}
}

void	draw_wall(int i, t_game *game, int bott_pix, int top_pix)
{
	int j;
	
	j = top_pix;
	while (j < bott_pix)
	{
		if (game->rays[i].horiz)
			mlx_put_pixel(game->game_img, i ,j, 0x000080FF);
		else
			mlx_put_pixel(game->game_img, i ,j, 0xAAAA80FF);
		j++;
	}
	j = 0;
	while (j < top_pix)
	{
		mlx_put_pixel(game->game_img, i, j, 0xFFFFFFFF);
		j++;
	}
	j = bott_pix;
	while (j <  SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->game_img, i, j, 0xFFD700FF);
		j++;
	}
}