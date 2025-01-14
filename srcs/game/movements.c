/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:25:49 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/14 18:21:30 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	can_move(float x, float y, t_game *game)
{
	float 	a[5][2];
	int 	j;
	int		x_coo;
	int		y_coo;

	j = 0;
	a[0][0] = y + game->pl_y_pix;
	a[0][1] = x + game->pl_x_pix;
	a[1][0] = y + game->pl_y_pix;
	a[1][1] = x + game->pl_x_pix + 2.0f;
	a[2][0] = y + game->pl_y_pix;
	a[2][1] = x + game->pl_x_pix - 2.0f;
	a[3][0] = y + game->pl_y_pix + 2.0f;
	a[3][1] = x + game->pl_x_pix;
	a[4][0] = y + game->pl_y_pix - 2.0f;
	a[4][1] = x + game->pl_x_pix;
	while (j < 3)
	{
		y_coo = (int)floor(a[j][0] / TILE_SIZE);
		x_coo = (int)floor(a[j][1] / TILE_SIZE);
		if (y_coo < 0 || y_coo >= game->map_inf->map_height || x_coo < 0
			|| x_coo >= ft_strlen(game->map[y_coo]))
			return (0);
		if (game->map[y_coo][x_coo] == '1')
			return (0) ;
		j++;
	}
	return (1);
}

void	update_map_l_r(t_game *game)
{
	float	x;
	float	y;
	float	p_step;

	p_step = game->pl_inf->turn_dir * PLYR_SPEED;
	if (game->pl_inf->rot_angle < 0)
		game->pl_inf->rot_angle = fmod(game->pl_inf->rot_angle, 2 * PI) + 2 * PI;
	else if (game->pl_inf->rot_angle > 2 * PI)
		game->pl_inf->rot_angle -= 2 * PI;
	x = p_step * cos(game->pl_inf->rot_angle - (PI / 2));
	y = p_step * sin(game->pl_inf->rot_angle - (PI / 2));
	if (can_move(x, y, game))
	{
		game->pl_y_pix += y;
		game->pl_x_pix += x;
		if (game->pl_x_pix / TILE_SIZE != game->pl_inf->pl_x
			|| game->pl_y_pix / TILE_SIZE != game->pl_inf->pl_y)
		{
			game->map[game->pl_inf->pl_y][game->pl_inf->pl_x] = '0';
			game->pl_inf->pl_x = game->pl_x_pix / TILE_SIZE;
			game->pl_inf->pl_y = game->pl_y_pix / TILE_SIZE;
			game->map[game->pl_inf->pl_y][game->pl_inf->pl_x] =
			game->pl_inf->pl_dir;
		}
	}
}

void	update_map_u_d(t_game *game)
{
	float	x;
	float	y;
	float	p_step;

	p_step = game->pl_inf->walk_dir * PLYR_SPEED;
	x = p_step * cos(game->pl_inf->rot_angle);
	y = p_step * sin(game->pl_inf->rot_angle);
	if (can_move(x, y, game))
	{
		game->pl_y_pix += y;
		game->pl_x_pix += x;
		if (game->pl_y_pix / TILE_SIZE != game->pl_inf->pl_y
			|| game->pl_x_pix / TILE_SIZE != game->pl_inf->pl_x)
		{
			game->map[game->pl_inf->pl_y][game->pl_inf->pl_x] = '0';
			game->pl_inf->pl_y = game->pl_y_pix / TILE_SIZE;
			game->pl_inf->pl_x = game->pl_x_pix / TILE_SIZE;
			game->map[game->pl_inf->pl_y][game->pl_inf->pl_x] =
			game->pl_inf->pl_dir;
		}
	}
}

void	render_move(t_game *game, char dir)
{
	if (dir == 'U' || dir == 'D')
	{
		if (dir == 'U')
			game->pl_inf->walk_dir = 1;
		else
			game->pl_inf->walk_dir = -1;
		update_map_u_d(game);
	}
	if (dir == 'L' || dir == 'R')
	{
		if (dir == 'L')
			game->pl_inf->turn_dir = 1;
		else
			game->pl_inf->turn_dir = -1;
		update_map_l_r(game);
	}
	game->render = true;
}

void	render_va(t_game *game, char dir)
{
	if(dir == 'L')
	{
		game->pl_inf->turn_dir = -3;
		game->pl_inf->rot_angle += game->pl_inf->turn_dir * RAY_ANG;
	}
	else if (dir == 'R')
	{
		game->pl_inf->turn_dir = 3;
		game->pl_inf->rot_angle += game->pl_inf->turn_dir * RAY_ANG;
	}
	if (game->pl_inf->rot_angle < 0)
		game->pl_inf->rot_angle = fmod(game->pl_inf->rot_angle, 2 * PI) + 2 * PI;
	else if (game->pl_inf->rot_angle > 2 * PI)
		game->pl_inf->rot_angle -= 2 * PI;
	game->render = true;
}
