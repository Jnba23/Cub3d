/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:43:32 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/28 02:38:09 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	deg2rad(double angle_deg)
{
	return (angle_deg * PI / 180);
}

double	rad2deg(double angle_rad)
{
	return ((angle_rad / PI) * 180);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

float	square(float i)
{
	return (i * i);
}
