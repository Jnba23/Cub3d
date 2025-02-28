/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:43:32 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/28 11:32:13 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

float	deg2rad(float angle_deg)
{
	return (angle_deg * PI / 180);
}

float	rad2deg(float angle_rad)
{
	return ((angle_rad / PI) * 180);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	square(float i)
{
	return (i * i);
}

bool	inside_strip(float x_pix, float y_pix)
{
	if (powf(x_pix - MINI_MAP_RADIUS, 2)
		+ powf(y_pix - MINI_MAP_RADIUS, 2) >= STRIP_RADIUS_SQUARE)
		return (1);
	return (0);
}
