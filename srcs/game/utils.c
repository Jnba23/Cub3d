/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:13 by asayad            #+#    #+#             */
/*   Updated: 2024/12/24 20:52:28 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	deg2rad(double angle_deg)
{
	return (angle_deg * M_PI / 180);
}

double	rad2deg(double angle_rad)
{
	return ((angle_rad / M_PI) * 180);
}

void	free_ressources(t_map *map_inf)
{
	(void) map_inf;
	return ;
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

float	square(float i)
{
	return (i * i);
}

void	reset_mvs_indic(t_game *game)
{
	game->pl_inf->turn_dir = 0;
	game->pl_inf->walk_dir = 0;
}
