/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:15 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/20 11:03:13 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	shortest_distance(t_game *game, int ray)
{
	float	d1;
	float	d2;

	d1 = sqrt(square(game->inter->hx) + square(game->inter->hy));
	d2 = sqrt(square(game->inter->vx) + square(game->inter->vy));
	if (d1 > d2)
	{
		game->rays[ray].horiz = true;
		game->rays[ray].x = game->pl_x_pix + game->inter->vx;
		game->rays[ray].y = game->pl_y_pix + game->inter->vy;
		game->rays[ray].d = d2;
	}
	else
	{
		game->rays[ray].horiz = false;
		game->rays[ray].x = game->pl_x_pix + game->inter->hx;
		game->rays[ray].y = game->pl_y_pix + game->inter->hy;
		game->rays[ray].d = d1;
	}
}

void	inter_horizontal(t_game *game, int ray)
{
	game->rays[ray].up = va_y_up(game->inter->alpha);
	game->rays[ray].right = va_x_right(game->inter->alpha);
	if (game->rays[ray].up)
		game->inter->hy = (game->pl_y_pix - (floor(game->pl_y_pix / TILE_SIZE)
					* TILE_SIZE)) * -1 + EPSILON ;
	else
		game->inter->hy = floor(game->pl_y_pix / TILE_SIZE)
			* TILE_SIZE - game->pl_y_pix + TILE_SIZE;
	game->inter->hx = (game->inter->hy / tan(game->inter->alpha));
	while (valid_ray_intersection(game, game->inter->hx, game->inter->hy))
	{
		if (game->rays[ray].up)
			game->inter->hy -= TILE_SIZE;
		else
			game->inter->hy += TILE_SIZE;
		game->inter->hx = game->inter->hy / tan(game->inter->alpha);
	}
}

void	inter_vertical(t_game *game, int ray)
{
	game->rays[ray].right = va_x_right(game->inter->alpha);
	game->rays[ray].up = va_y_up(game->inter->alpha);
	if (game->rays[ray].right)
		game->inter->vx = floor(game->pl_x_pix / TILE_SIZE) * TILE_SIZE
			- game->pl_x_pix + TILE_SIZE;
	else
		game->inter->vx = (game->pl_x_pix - (floor(game->pl_x_pix / TILE_SIZE)
					* TILE_SIZE)) * -1 + EPSILON;
	game->inter->vy = game->inter->vx * tan(game->inter->alpha);
	while (valid_ray_intersection(game, game->inter->vx, game->inter->vy))
	{
		if (game->rays[ray].right)
			game->inter->vx += TILE_SIZE;
		else
			game->inter->vx -= TILE_SIZE;
		game->inter->vy = game->inter->vx * tan(game->inter->alpha);
	}
}
