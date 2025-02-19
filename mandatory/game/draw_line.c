/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:14:49 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/19 19:14:00 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	render_ray(t_game *game, t_coor *coo)
{
	coo->x0 = (int)MINI_MAP_RADIUS;
	coo->y0 = (int)MINI_MAP_RADIUS;
	coo->dx = abs(coo->x1 - coo->x0);
	coo->dy = abs(coo->y1 - coo->y0);
	if (coo->x0 < coo->x1)
		coo->sx = 1 ;
	else
		coo->sx = -1;
	if (coo->y0 < coo->y1)
		coo->sy = 1;
	else
		coo->sy = -1;
	coo->dec_param = coo->dx - coo->dy;
	draw_ray(game, coo);
}

void	draw_ray(t_game *game, t_coor *coo)
{
	int	d_p;

	while (1)
	{
		mlx_put_pixel(game->mmap_image, coo->x0, coo->y0, 0xFF0000FF);
		if (abs(coo->x0 - coo->x1) <= 1 && abs(coo->y0 - coo->y1) <= 1)
			break ;
		d_p = coo->dec_param * 2;
		if (d_p > -coo->dy)
		{
			coo->dec_param -= coo->dy;
			coo->x0 += coo->sx;
		}
		if (d_p < coo->dx)
		{
			coo->dec_param += coo->dx;
			coo->y0 += coo->sy;
		}
	}
}
