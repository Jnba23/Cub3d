/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:15 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/28 04:30:49 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	shortest_distance(t_game *game)
{
	int	d1;
	int	d2;
	
	d1 = sqrt(square(game->inter->hx) + square(game->inter->hy));
	d2 = sqrt(square(game->inter->vx) + square(game->inter->vy));
	if (d1 > d2)
	{
		game->rays->x = game->pl_x_pix + game->inter->vx;
		game->rays->y = game->pl_y_pix + game->inter->vy;
	}
	else
	{
		game->rays->x = game->pl_x_pix + game->inter->hx;
		game->rays->y = game->pl_y_pix + game->inter->hy;
	}
}

void	inter_horizontal(t_game *game)
{
	game->rays->up = va_y_up(game->inter->alpha);
	game->rays->right = va_x_right(game->inter->alpha);
	if (game->rays->up)
		game->inter->hy = (game->pl_y_pix - (game->pl_inf->pl_y
						* TILE_SIZE - 1)) * -1;
	else
		game->inter->hy = (game->pl_inf->pl_y * TILE_SIZE + TILE_SIZE)
						- game->pl_y_pix;
	game->inter->hx =  (game->inter->hy / tan(game->inter->alpha));
	if (valid_ray_intersection(game, game->inter->hx, game->inter->hy))
	{
		while (valid_ray_intersection(game, game->inter->hx, game->inter->hy))
		{
			if (game->rays->up)
				game->inter->hy -= TILE_SIZE;
			else
				game->inter->hy += TILE_SIZE;
			game->inter->hx = game->inter->hy / tan(game->inter->alpha);
		}
	}
}

void	inter_vertical(t_game *game)
{
	game->rays->up = va_y_up(game->inter->alpha);
	game->rays->right = va_x_right(game->inter->alpha);
	if (game->rays->right)
		game->inter->vx = (game->pl_inf->pl_x * TILE_SIZE + TILE_SIZE)
		- game->pl_x_pix;
	else
		game->inter->vx = (game->pl_x_pix
					- (game->pl_inf->pl_x * TILE_SIZE - 1)) * -1;
	game->inter->vy =  game->inter->vx * tan(game->inter->alpha);
	if (valid_ray_intersection(game, game->inter->vx, game->inter->vy))
	{
		while (valid_ray_intersection(game, game->inter->vx, game->inter->vy))
		{
			if (game->rays->right)
				game->inter->vx += TILE_SIZE;
			else
				game->inter->vx -= TILE_SIZE;
			game->inter->vy = game->inter->vx * tan(game->inter->alpha);
		}
	}
}
