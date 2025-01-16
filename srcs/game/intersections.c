/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:15 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/16 11:45:09 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	shortest_distance(t_game *game, int ray)
{
	float	d1;
	float	d2;
	
	d1 = sqrt(square(game->rays->inter->hx) + square(game->rays->inter->hy));
	d2 = sqrt(square(game->rays->inter->vx) + square(game->rays->inter->vy));
	if (d1 > d2)
	{
		game->rays[ray].x = game->pl_x_pix + game->rays->inter->vx;
		game->rays[ray].y = game->pl_y_pix + game->rays->inter->vy;
		game->rays[ray].horiz = true;
		game->rays[ray].d = d2;
	}
	else
	{
		game->rays[ray].x = game->pl_x_pix + game->rays->inter->hx;
		game->rays[ray].y = game->pl_y_pix + game->rays->inter->hy;
		game->rays[ray].horiz = false;
		game->rays[ray].d = d1;
	}
}

void	inter_horizontal(t_game *game, int ray)
{
	game->rays[ray].up = va_y_up(game->rays[ray].alpha);
	game->rays[ray].right = va_x_right(game->rays[ray].alpha);
	if (game->rays[ray].up)
		game->rays[ray].inter->hy = (game->pl_y_pix - (game->pl_inf->pl_y
						* TILE_SIZE - 1)) * -1;
	else
		game->rays[ray].inter->hy = (game->pl_inf->pl_y * TILE_SIZE + TILE_SIZE)
						- game->pl_y_pix;
	game->rays[ray].inter->hx =  (game->rays[ray].inter->hy / tan(game->rays[ray].alpha));
	if (valid_ray_intersection(game, game->rays[ray].inter->hx, game->rays[ray].inter->hy))
	{
		while (valid_ray_intersection(game, game->rays[ray].inter->hx, game->rays[ray].inter->hy))
		{
			if (game->rays[ray].up)
				game->rays[ray].inter->hy -= TILE_SIZE;
			else
				game->rays[ray].inter->hy += TILE_SIZE;
			game->rays[ray].inter->hx = game->rays[ray].inter->hy / tan(game->rays[ray].alpha);
		}
	}
}

void	inter_vertical(t_game *game, int ray)
{
	game->rays[ray].up = va_y_up(game->rays[ray].alpha);
	game->rays[ray].right = va_x_right(game->rays[ray].alpha);
	if (game->rays[ray].right)
		game->rays[ray].inter->vx = (game->pl_inf->pl_x * TILE_SIZE + TILE_SIZE)
		- game->pl_x_pix;
	else
		game->rays[ray].inter->vx = (game->pl_x_pix
					- (game->pl_inf->pl_x * TILE_SIZE - 1)) * -1;
	game->rays[ray].inter->vy =  game->rays[ray].inter->vx * tan(game->rays[ray].alpha);
	if (valid_ray_intersection(game, game->rays[ray].inter->vx, game->rays[ray].inter->vy))
	{
		while (valid_ray_intersection(game, game->rays[ray].inter->vx, game->rays[ray].inter->vy))
		{
			if (game->rays[ray].right)
				game->rays[ray].inter->vx += TILE_SIZE;
			else
				game->rays[ray].inter->vx -= TILE_SIZE;
			game->rays[ray].inter->vy = game->rays[ray].inter->vx * tan(game->rays[ray].alpha);
		}
	}
}
