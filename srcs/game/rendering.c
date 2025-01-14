/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:06 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/13 20:03:56 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_wall(int i, t_game *game, int bott_pix, int top_pix)
{
	int j;
	
	j = top_pix;
	while (j < bott_pix)
	{
		mlx_put_pixel(game->game_win, i ,j, 0x000080FF);
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
		mlx_put_pixel(game->game_win, i, j, 0xFFD700FF);
		j++;
	}
}

void render_wall(t_game *game, int ray)
{
	float	wall_h;
	int		bott_pix;
	int		top_pix;
    float	angle_beta;
	
	angle_beta = game->inter->alpha - game->pl_inf->rot_angle;
	game->d *= cos(angle_beta);
	wall_h = ((float)TILE_SIZE / (float)game->d) * ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
	bott_pix = SCREEN_HEIGHT / 2 + wall_h / 2;
	if (bott_pix > SCREEN_HEIGHT)
		bott_pix = SCREEN_HEIGHT;
	top_pix = SCREEN_HEIGHT / 2 - wall_h / 2;
	if (top_pix < 0)
		top_pix = 0;
	draw_wall(ray, game, bott_pix, top_pix);
}

void	render_rays(t_game *game)
{
	int		ray;
	float	max_ang;

	ray = 0;
	max_ang = game->pl_inf->rot_angle + deg2rad(FOV / 2.0);
	game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
	normalize_ang(&game->inter->alpha, &max_ang);
	while (ray < SCREEN_WIDTH && game->inter->alpha <= max_ang)
	{
		inter_horizontal(game);
		inter_vertical(game);
		shortest_distance(game);
		render_wall(game, ray);
		// render_ray(game);
		ray++;
		game->inter->alpha += deg2rad(RAY_ANG);
		if (game->inter->alpha > 2 * PI)
		{
			game->inter->alpha -= 2 * PI;
			max_ang -= 2 * PI;
		}
	}
}

// void	render_rays(t_game *game)
// {
// 	float	max_ang;

// 	max_ang = game->pl_inf->rot_angle + deg2rad(FOV / 2.0);
// 	game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
// 	normalize_ang(&game->inter->alpha, &max_ang);
// 	while (game->inter->alpha <= max_ang)
// 	{
// 		inter_horizontal(game);
// 		inter_vertical(game);
// 		shortest_distance(game);
// 		render_ray(game);
// 		game->inter->alpha += deg2rad(RAY_ANG);
// 		if (game->inter->alpha > 2 * PI)
// 		{
// 			game->inter->alpha -= 2 * PI;
// 			max_ang -= 2 * PI;
// 		}
// 	}
// 	// reset_mvs_indic(game);
// }

void	move_player(void *game)
{
	t_game 		*gm;

	gm = (t_game *)game;
	if (mlx_is_key_down(gm->game, MLX_KEY_W))
		render_move(gm, 'U');
	if (mlx_is_key_down(gm->game, MLX_KEY_S))
		render_move(gm, 'D');
	if (mlx_is_key_down(gm->game, MLX_KEY_A))
		render_move(gm, 'L');
	if (mlx_is_key_down(gm->game, MLX_KEY_D))
		render_move(gm, 'R');
	if (mlx_is_key_down(gm->game, MLX_KEY_LEFT))
		render_va(gm, 'L');
	if (mlx_is_key_down(gm->game, MLX_KEY_RIGHT))
		render_va(gm, 'R');
	if (gm->render)
	{
		render_2D_map(gm);
		gm->render = false;
	}
}

void	render_2D_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_pix_h)
	{
		x = 0;
		while (x < game->map_pix_w)
		{
			if (game->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
			{
				if (y % TILE_SIZE == 0 || x % TILE_SIZE == 0)
					mlx_put_pixel(game->game_win, x, y, 0x00000000);
				else
					mlx_put_pixel(game->game_win, x, y, 0x000080FF);
			}
			else
			{
				if (y % TILE_SIZE == 0 || x % TILE_SIZE == 0)
					mlx_put_pixel(game->game_win, x, y, 0x00000000);
				else
					mlx_put_pixel(game->game_win, x, y, 0xFFD700FF);
			}
			x++;
		}
		y++;
	}
	render_player(game);
}

void	render_player(t_game *game)
{
    float i;
    float j;

	j = game->pl_inf->pl_y * (float)TILE_SIZE;
	while(j <= game->pl_inf->pl_y * (float)TILE_SIZE
		+ fmod(game->pl_y_pix, (float)TILE_SIZE))
	{
		i = game->pl_inf->pl_x * (float)TILE_SIZE;
		while (i <=  game->pl_inf->pl_x
			* (float)TILE_SIZE + fmod(game->pl_x_pix, (float)TILE_SIZE))
		{
			if (i ==  game->pl_inf->pl_x * (float)TILE_SIZE
				+ fmod(game->pl_x_pix, (float)TILE_SIZE) 
				&& j == game->pl_inf->pl_y * (float)TILE_SIZE
				+ fmod(game->pl_y_pix, (float)TILE_SIZE))
				mlx_put_pixel(game->game_win, i, j, 0xFF0000FF);
			i++;
		}
		j++;
	}
	render_rays(game);
}
