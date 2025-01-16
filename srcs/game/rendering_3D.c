/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:29:31 by asayad            #+#    #+#             */
/*   Updated: 2025/01/16 11:45:35 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void render_3D(t_game *game)
{
	float	wall_h;
	float	bott_pix;
	float	top_pix;
    float	angle_beta;
	int		i;
	i = 0;

	while (i < SCREEN_WIDTH)
	{
		angle_beta = game->rays[i].alpha - game->pl_inf->rot_angle;
		game->rays[i].d *= cos(angle_beta);
		wall_h = ((float)TILE_SIZE / (float)game->rays[i].d) * (float)((SCREEN_WIDTH / 2.0) / (float)tan(deg2rad(FOV / 2.0)));
		bott_pix = (float)(SCREEN_HEIGHT / 2.0) + (float)(wall_h / 2.0);
		if (bott_pix > SCREEN_HEIGHT)
			bott_pix = SCREEN_HEIGHT;
		top_pix = (float)(SCREEN_HEIGHT / 2.0) - (float)(wall_h / 2.0);
		if (top_pix < 0)
			top_pix = 0;
		draw_wall(i, game, (int)bott_pix, (int)top_pix);
		i++;
	}
}

void	draw_wall(int i, t_game *game, int bott_pix, int top_pix)
{
	int j;
	
	j = top_pix;
	while (j < bott_pix)
	{
		if (game->rays[i].horiz)
			mlx_put_pixel(game->game_win, i, j, 0xFF0000FF);
		else
			mlx_put_pixel(game->game_win, i, j, 0xAA0000DD);
		j++;
	}
	j = 0;
	while (j < top_pix)
	{
		mlx_put_pixel(game->game_win, i, j, 0xFFFFFFFF);
		j++;
	}
	j = bott_pix;
	while (j <  SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->game_win, i ,j, 0x000080FF);		
		j++;
	}
}
