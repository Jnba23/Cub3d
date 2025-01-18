/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:43:32 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/18 21:25:12 by asayad           ###   ########.fr       */
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

double	square(double i)
{
	return (i * i);
}
