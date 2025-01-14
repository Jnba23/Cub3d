/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:15 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/14 18:57:56 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	shortest_distance(t_game *game)
{
	float	d1;
	float	d2;
	
	d1 = sqrt(square(game->inter->hx) + square(game->inter->hy));
	d2 = sqrt(square(game->inter->vx) + square(game->inter->vy));
	if (d1 > d2)
	{
		game->rays->x = game->pl_x_pix + game->inter->vx;
		game->rays->y = game->pl_y_pix + game->inter->vy;
		game->d = d2;
	}
	else
	{
		game->rays->x = game->pl_x_pix + game->inter->hx;
		game->rays->y = game->pl_y_pix + game->inter->hy;
		game->d = d1;
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
			// if (game->inter->alpha > 0 || game->inter->alpha < PI / 2 || game->inter->alpha > PI || game->inter->alpha < 3 * PI / 2)
			// 	printf("Horiz ray alpha : %f\n", rad2deg(game->inter->alpha));
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
			// if (game->inter->alpha > 0 || game->inter->alpha < PI / 2 || game->inter->alpha > PI || game->inter->alpha < 3 * PI / 2)
			// 	printf("Verti ray alpha : %f\n", rad2deg(game->inter->alpha));
		}
	}
}

// void inter_horizontal(t_game *game)
// {
//     game->rays->up = va_y_up(game->inter->alpha);
//     game->rays->right = va_x_right(game->inter->alpha);

//     if (game->rays->up)
//         game->inter->hy = (game->pl_y_pix - (game->pl_inf->pl_y * TILE_SIZE - 1)) * -1;
//     else
//         game->inter->hy = (game->pl_inf->pl_y * TILE_SIZE + TILE_SIZE) - game->pl_y_pix;

//     // Avoid division by zero for vertical rays
//     if (sin(game->inter->alpha) != 0)
//         game->inter->hx = game->inter->hy / tan(game->inter->alpha);
//     else
//         game->inter->hx = 0;

//     if (valid_ray_intersection(game, game->inter->hx, game->inter->hy))
//     {
//         while (valid_ray_intersection(game, game->inter->hx, game->inter->hy))
//         {
//             if (game->rays->up)
//                 game->inter->hy -= TILE_SIZE;
//             else
//                 game->inter->hy += TILE_SIZE;

//             if (sin(game->inter->alpha) != 0)
//                 game->inter->hx = game->inter->hy / tan(game->inter->alpha);
//         }
//     }
// }

// void inter_vertical(t_game *game)
// {
//     game->rays->up = va_y_up(game->inter->alpha);
//     game->rays->right = va_x_right(game->inter->alpha);

//     if (game->rays->right)
//         game->inter->vx = (game->pl_inf->pl_x * TILE_SIZE + TILE_SIZE) - game->pl_x_pix;
//     else
//         game->inter->vx = (game->pl_x_pix - (game->pl_inf->pl_x * TILE_SIZE - 1)) * -1;

//     // Avoid multiplication by zero for horizontal rays
//     if (cos(game->inter->alpha) != 0)
//         game->inter->vy = game->inter->vx * tan(game->inter->alpha);
//     else
//         game->inter->vy = 0;

//     if (valid_ray_intersection(game, game->inter->vx, game->inter->vy))
//     {
//         while (valid_ray_intersection(game, game->inter->vx, game->inter->vy))
//         {
//             if (game->rays->right)
//                 game->inter->vx += TILE_SIZE;
//             else
//                 game->inter->vx -= TILE_SIZE;

//             if (cos(game->inter->alpha) != 0)
//                 game->inter->vy = game->inter->vx * tan(game->inter->alpha);
//         }
//     }
// }
