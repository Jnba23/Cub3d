/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:20:42 by asayad            #+#    #+#             */
/*   Updated: 2025/01/18 23:26:30 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void render_3D_game(t_game *game)
{
	double	wall_h;
	int		bott_pix;
	int		top_pix;
    double	angle_beta;
    int     i;

    i = -1;
    game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
    normalize_ang(&game->inter->alpha);
	while (++i < SCREEN_WIDTH)
    {
        angle_beta = game->inter->alpha - game->pl_inf->rot_angle;
	    game->rays[i].d *= cos(angle_beta);
        if (!cos(angle_beta) || !game->rays[i].d)
            game->rays[i].d = 1;
        wall_h = ((double)TILE_SIZE / (double)game->rays[i].d) * ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
        bott_pix = SCREEN_HEIGHT / 2 + wall_h / 2;
        if (bott_pix > SCREEN_HEIGHT)
            bott_pix = SCREEN_HEIGHT;
        top_pix = SCREEN_HEIGHT / 2 - wall_h / 2;
        if (top_pix < 0)
            top_pix = 0;
        draw_wall(i, game, bott_pix, top_pix);
        game->inter->alpha += game->ray_ang;
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