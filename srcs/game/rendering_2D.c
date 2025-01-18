/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_2D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:06 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/18 23:39:54 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cube3d(void *game)
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
		// render_2D_map(gm);
		cast_rays(gm);
		render_3D_game(gm);
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
					mlx_put_pixel(game->game_img, x, y, 0x00000000);
				else
					mlx_put_pixel(game->game_img, x, y, 0x000080FF);
			}
			else
			{
				if (y % TILE_SIZE == 0 || x % TILE_SIZE == 0)
					mlx_put_pixel(game->game_img, x, y, 0x00000000);
				else
					mlx_put_pixel(game->game_img, x, y, 0xFFD700FF);
			}
			x++;
		}
		y++;
	}
	render_player(game);
}

void	render_player(t_game *game)
{
    double i;
    double j;

	j = game->pl_inf->pl_y * (double)TILE_SIZE;
	while(j <= game->pl_inf->pl_y * (double)TILE_SIZE
		+ fmod(game->pl_y_pix, (double)TILE_SIZE))
	{
		i = game->pl_inf->pl_x * (double)TILE_SIZE;
		while (i <=  game->pl_inf->pl_x
			* (double)TILE_SIZE + fmod(game->pl_x_pix, (double)TILE_SIZE))
		{
			if (i ==  game->pl_inf->pl_x * (double)TILE_SIZE
				+ fmod(game->pl_x_pix, (double)TILE_SIZE) 
				&& j == game->pl_inf->pl_y * (double)TILE_SIZE
				+ fmod(game->pl_y_pix, (double)TILE_SIZE))
				mlx_put_pixel(game->game_img, i, j, 0xFF0000FF);
			i++;
		}
		j++;
	}
}

