/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:14:49 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/18 23:05:14 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void render_ray(t_game *game, int ray)
{
    t_coor	coo;
    int		d_p;

    coo.x0 = (int)game->pl_x_pix;
    coo.y0 = (int)game->pl_y_pix;
    coo.x1 = game->rays[ray].x;
    coo.y1 = game->rays[ray].y;
    coo.dx = abs(coo.x1 - coo.x0);
    coo.dy = abs(coo.y1 - coo.y0);
    if (coo.x0 < 0 || coo.x0 >= SCREEN_HEIGHT || 
        coo.y0 < 0 || coo.y0 >= SCREEN_HEIGHT)
    {
        return;
    }
	if (coo.x0 < coo.x1)
    {
        coo.sx = 1 ;
    }
	else
	{
        coo.sx = -1;
    }
	if (coo.y0 < coo.y1)
    {
        coo.sy = 1;
    }
	else
	{
        coo.sy = -1;
    }
    coo.dec_param = coo.dx - coo.dy;
    while (1)
    {
        if (game->rays[ray].horiz)
		    mlx_put_pixel(game->game_img, coo.x0, coo.y0, 0xFF0000FF);
        else
		    mlx_put_pixel(game->game_img, coo.x0, coo.y0, 0xF00BB0AA);
        if (abs(coo.x0 - coo.x1) <= 1 && abs(coo.y0 - coo.y1) <= 1)
            break ;
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
