/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:25:49 by hmoukit           #+#    #+#             */
/*   Updated: 2025/03/01 13:39:52 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	can_move(float x, float y, t_game *game)
{
	float	a[3][2];
	int		j;
	int		x_coo;
	int		y_coo;

	j = 0;
	a[0][0] = y + game->pl_y_pix;
	a[0][1] = x + game->pl_x_pix;
	a[1][0] = y + game->pl_y_pix + 3.0f;
	a[1][1] = x + game->pl_x_pix + 3.0f;
	a[2][0] = y + game->pl_y_pix - 3.0f;
	a[2][1] = x + game->pl_x_pix - 3.0f;
	while (j < 3)
	{
		y_coo = (int)floor(a[j][0] / TILE_SIZE);
		x_coo = (int)floor(a[j][1] / TILE_SIZE);
		if (y_coo < 0 || y_coo >= game->map_inf->map_height || x_coo < 0
			|| x_coo >= ft_strlen(game->map[y_coo]))
			return (0);
		if (game->map[y_coo][x_coo] == '1')
			return (0);
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

void	render_va(t_game *game, char dir)
{
	if (dir == 'L')
	{
		game->pl_inf->turn_dir = -3;
		game->pl_inf->rot_angle += game->pl_inf->turn_dir * game->ang_increment;
	}
	else if (dir == 'R')
	{
		game->pl_inf->turn_dir = 3;
		game->pl_inf->rot_angle += game->pl_inf->turn_dir * game->ang_increment;
	}
	if (game->pl_inf->rot_angle < 0)
		game->pl_inf->rot_angle = fmod(game->pl_inf->rot_angle, 2 * PI)
			+ 2 * PI;
	else if (game->pl_inf->rot_angle > 2 * PI)
		game->pl_inf->rot_angle -= 2 * PI;
	game->render = true;
}
