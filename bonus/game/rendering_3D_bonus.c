/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:20:42 by asayad            #+#    #+#             */
/*   Updated: 2025/02/18 18:43:59 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void render_3D_game(t_game *game)
{
    float angle_beta;
    float min_distance;
    int i;
	int wall_center;
    game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
	min_distance = TILE_SIZE * 0.1;
	i = -1;
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
        wall_center = SCREEN_HEIGHT / 2;
        game->rays[i].top_pix = wall_center - (game->rays[i].wall_h / 2);
        game->rays[i].bott_pix = wall_center + (game->rays[i].wall_h / 2);
        game->rays[i].bott_pix = (game->rays[i].bott_pix > SCREEN_HEIGHT) ? 
                                 SCREEN_HEIGHT : game->rays[i].bott_pix;
        game->rays[i].top_pix = (game->rays[i].top_pix < 0) ? 0 : game->rays[i].top_pix;
        if (game->rays[i].hit_door)
            draw_texture(game, i, 'd');
        else
			draw_texture(game, i, 'w');
        draw_ceiling_floor(i, game, game->rays[i].bott_pix, game->rays[i].top_pix);
        game->inter->alpha += game->ray_ang;
        normalize_ang(&game->inter->alpha);
    }
}

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