/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:25:49 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/18 19:30:40 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	can_move(float x, float y, t_game *game)
{
	float 	a[3][2];
	int 	j;
	int		x_coo;
	int		y_coo;

	j = 0;
	a[0][0] = y + game->pl_y_pix;
	a[0][1] = x + game->pl_x_pix;
	a[1][0] = y + game->pl_y_pix + 0.001f;
	a[1][1] = x + game->pl_x_pix + 0.001f;
	a[2][0] = y + game->pl_y_pix - 0.001f;
	a[2][1] = x + game->pl_x_pix - 0.001f;
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
		int prev_x = game->pl_inf->pl_x;
		int prev_y = game->pl_inf->pl_y;
		game->pl_y_pix += y;
		game->pl_x_pix += x;
		int new_x = game->pl_x_pix / TILE_SIZE;
		int new_y = game->pl_y_pix / TILE_SIZE;
		if (new_x != prev_x || new_y != prev_y)
		{
			if (game->inside_door)
			{
				game->map[prev_y][prev_x] = 'D';
				game->inside_door = 0;
			}
			else
				game->map[prev_y][prev_x] = '0';
			if (game->map[new_y][new_x] == 'D')
			{
				game->inside_door = 1;
				game->map[new_y][new_x] = '0';
			}
			game->pl_inf->pl_x = new_x;
			game->pl_inf->pl_y = new_y;
			game->map[new_y][new_x] = game->pl_inf->pl_dir;
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
		int prev_x = game->pl_inf->pl_x;
		int prev_y = game->pl_inf->pl_y;
		game->pl_y_pix += y;
		game->pl_x_pix += x;
		int new_x = game->pl_x_pix / TILE_SIZE;
		int new_y = game->pl_y_pix / TILE_SIZE;
		if (new_x != prev_x || new_y != prev_y)
		{
			if (game->inside_door)
			{
				game->map[prev_y][prev_x] = 'D';
				game->inside_door = 0;
			}
			else
				game->map[prev_y][prev_x] = '0';
			if (game->map[new_y][new_x] == 'D')
			{
				game->inside_door = 1;
				game->map[new_y][new_x] = '0';
			}
			game->pl_inf->pl_x = new_x;
			game->pl_inf->pl_y = new_y;
			game->map[new_y][new_x] = game->pl_inf->pl_dir;
		}
	}
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

void	quit_game(t_game *game)
{
	free_table(&game->map_inf, game->map_inf->map_size);
	// free_textures(&game->map_inf);
	if (game->mmap_inf->n)
		mlx_delete_image(game->game, game->mmap_inf->n);
	if (game->text->img_east)
		mlx_delete_image(game->game, game->text->img_east);
	if (game->text->img_west)
		mlx_delete_image(game->game, game->text->img_west);
	if (game->text->img_north)
		mlx_delete_image(game->game, game->text->img_north);
	if (game->text->img_south)
		mlx_delete_image(game->game, game->text->img_south);
	delete_images(game);
	exit(1);
}