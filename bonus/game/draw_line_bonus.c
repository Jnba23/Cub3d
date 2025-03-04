/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:14:49 by hmoukit           #+#    #+#             */
/*   Updated: 2025/03/01 13:23:14 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	render_ray(t_game *game, t_coor *coo)
{
	coo->x0 = (int)game->mmap_radius;
	coo->y0 = (int)game->mmap_radius;
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
