/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:13 by asayad            #+#    #+#             */
/*   Updated: 2024/12/10 20:25:24 by asayad           ###   ########.fr       */
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

float	ft_abs(float i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

void	normalize_angle(float *angle)
{
	*angle = fmod(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle += 2 * M_PI;
}

float	x_scaled_mmp(int i, t_game *game_inf)
{
	float x;

	return (x = (i + game_inf->player_inf->player_x) * game_inf->scale);
}

float	y_scaled_mmp(int i, t_game *game_inf)
{
	float y;

	return (y = (i + game_inf->player_inf->player_y) * game_inf->scale);
}
