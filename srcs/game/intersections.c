/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:15 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/24 20:57:55 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	va_y_up(float va)
{
	if ((va >= 0 && va <= M_PI))
		return (0);
	return (1);
}

int	va_x_right(float va)
{
	if ((va >= 0 && va <= M_PI / 2) || (va >= (3 * M_PI) / 2.0 && va <= 2 * M_PI))
		return (1);
	return (0);
}

bool valid_ray_intersection(t_game *game, float hx, float hy)
{
    return (floor((game->pl_y_pix + hy) / TILE_SIZE) >= 0 &&
            floor((game->pl_y_pix + hy) / TILE_SIZE) < game->map_inf->map_height
			&& floor((game->pl_x_pix + hx) / TILE_SIZE) >= 0
			&& floor((game->pl_x_pix + hx) / TILE_SIZE)
			< ft_strlen(game->map[(int)floor((game->pl_y_pix + hy) / TILE_SIZE)])
			&& game->map[(int)floor((game->pl_y_pix + hy) / TILE_SIZE)]
            [(int)floor((game->pl_x_pix + hx) / TILE_SIZE)] != '1');
}

void	inter_horizontal(t_game *game)
{
	game->rays->up = va_y_up(game->inter->alpha);
	game->rays->right = va_x_right(game->inter->alpha);
	if (fabs(game->inter->alpha - M_PI) <= 0.001
		|| fabs(game->inter->alpha) <= 0.001)
	{
		game->inter->edge = true;
		game->inter->hy = 0;
		if (game->rays->right)
			game->inter->hx = TILE_SIZE;
		else
			game->inter->hx = -1 * TILE_SIZE;
	}
	else
	{
		if (game->rays->up)
			game->inter->hy = (game->pl_y_pix - (game->pl_inf->pl_y
							* TILE_SIZE - 1)) * -1;
		else
			game->inter->hy = (game->pl_inf->pl_y * TILE_SIZE + TILE_SIZE)
							- game->pl_y_pix;
		game->inter->hx =  (game->inter->hy / tan(game->inter->alpha));
	}
	if (valid_ray_intersection(game, game->inter->hx, game->inter->hy))
	{
		while (valid_ray_intersection(game, game->inter->hx, game->inter->hy))
		{
			if (game->rays->up)
				game->inter->hy -= TILE_SIZE;
			else
				game->inter->hy += TILE_SIZE;
			if (!game->inter->edge)
				game->inter->hx = game->inter->hy / tan(game->inter->alpha);
			else
			{
				if (game->rays->right)
					game->inter->hx += TILE_SIZE;
				else
					game->inter->hx -= TILE_SIZE;
			}
		}
	}
	game->inter->edge = false;
}

void	inter_vertical(t_game *game)
{
	game->rays->up = va_y_up(game->inter->alpha);
	game->rays->right = va_x_right(game->inter->alpha);
	if (fabs(game->inter->alpha - M_PI_2) <= 0.001
		|| fabs(game->inter->alpha - 3 * M_PI_2) <= 0.001)
	{
		game->inter->edge = true;
		game->inter->vy = 0;
		if (game->rays->right)
			game->inter->vx = TILE_SIZE;
		else
			game->inter->vx = (-1) * TILE_SIZE;
	}
	else
	{
		if (game->rays->right)
			game->inter->vx = (game->pl_inf->pl_x * TILE_SIZE + TILE_SIZE)
			- game->pl_x_pix;
		else
			game->inter->vx = (game->pl_x_pix
							- (game->pl_inf->pl_x * TILE_SIZE - 1)) * -1;
		game->inter->vy =  game->inter->vx * tan(game->inter->alpha);
	}
	if (valid_ray_intersection(game, game->inter->vx, game->inter->vy))
	{
		while (valid_ray_intersection(game, game->inter->vx, game->inter->vy))
		{
			if (game->rays->right)
				game->inter->vx += TILE_SIZE;
			else
				game->inter->vx -= TILE_SIZE;
			if (!game->inter->edge)
				game->inter->vy = game->inter->vx * tan(game->inter->alpha);
			else
			{
				if (!game->rays->up)
					game->inter->vy += TILE_SIZE;
				else
					game->inter->vy -= TILE_SIZE;
			}
		}
	}
	game->inter->edge = false;
}

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

void render_ray(t_game *game)
{
    t_coor	coo;
    int		d_p;
	
    coo.x0 = (int)game->pl_x_pix;
    coo.y0 = (int)game->pl_y_pix;
    coo.x1 = game->rays->x;
    coo.y1 = game->rays->y;
    coo.dx = abs(coo.x1 - coo.x0);
    coo.dy = abs(coo.y1 - coo.y0);
    if (coo.x0 < 0 || coo.x0 >= SCREEN_HEIGHT || 
        coo.y0 < 0 || coo.y0 >= SCREEN_HEIGHT)
        return;
	if (coo.x0 < coo.x1)
    	coo.sx = 1 ;
	else
		coo.sx = -1;
	if (coo.y0 < coo.y1)
    	coo.sy = 1;
	else
		coo.sy = -1;
    coo.dec_param = coo.dx - coo.dy;
    while (1)
    {
		if (!can_you_move(coo.x0, coo.y0, game))
			break ;
		mlx_put_pixel(game->game_win, coo.x0, coo.y0, 0xFF0000FF);
        if (abs(coo.x0 - coo.x1) <= 1 && abs(coo.y0 - coo.y1) <= 1)
            break;
        d_p = coo.dec_param * 2;
        if (d_p > -coo.dy)
        {
            coo.dec_param -= coo.dy;
            coo.x0 += coo.sx;
        }
        if (d_p < coo.dx)
        {
            coo.dec_param += coo.dx;
            coo.y0 += coo.sy;
        }
    }
}
