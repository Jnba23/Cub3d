/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:20:42 by asayad            #+#    #+#             */
/*   Updated: 2025/01/23 18:04:35 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void render_3D_game(t_game *game)
{
	float	angle_beta;
	int		i;
	i = -1;
	game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
	normalize_ang(&game->inter->alpha);
	while (++i < SCREEN_WIDTH)
	{
		angle_beta = game->inter->alpha - game->pl_inf->rot_angle;
		game->rays[i].d *= cos(angle_beta);
		if (!cos(angle_beta) || !game->rays[i].d)
		    game->rays[i].d = 1;
		game->rays[i].wall_h = ((float)TILE_SIZE / (float)game->rays[i].d) * ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
		game->rays[i].bott_pix = SCREEN_HEIGHT / 2 + game->rays[i].wall_h / 2;
		if (game->rays[i].bott_pix > SCREEN_HEIGHT)
		    game->rays[i].bott_pix = SCREEN_HEIGHT;
		game->rays[i].top_pix = SCREEN_HEIGHT / 2 - game->rays[i].wall_h / 2;
		if (game->rays[i].top_pix < 0)
		    game->rays[i].top_pix = 0;
		draw_ceiling_floor(i, game, game->rays[i].bott_pix, game->rays[i].top_pix);
		if (!draw_textured_wall(game, i))
			printf("draw_textured_wall returned 0\n");
		// draw_wall(i, game, game->rays[i].bott_pix, game->rays[i].top_pix);
		game->inter->alpha += game->ray_ang;
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