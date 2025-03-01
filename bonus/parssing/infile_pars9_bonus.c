/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars9_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:43:19 by asayad            #+#    #+#             */
/*   Updated: 2025/02/28 23:44:06 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	north_south(t_map *map_inf, char *s)
{
	if (!strcmp(s, "no"))
	{
		if (map_inf->ea != 0 || map_inf->so != 0
			|| map_inf->we != 0 || map_inf->no > 1)
			return (0);
	}
	if (!strcmp(s, "so"))
	{
		if (map_inf->no != 1 || (map_inf->ea != 0
				|| map_inf->we != 0 || map_inf->so > 1))
			return (0);
	}
	return (1);
}

int	east_west(t_map *map_inf, char *s)
{
	if (!strcmp(s, "we"))
	{
		if ((map_inf->no != 1 || map_inf->so != 1) || map_inf->ea != 0
			|| map_inf->we > 1)
			return (0);
	}
	if (!strcmp(s, "ea"))
	{
		if (map_inf->no != 1 || map_inf->so != 1 || map_inf->we != 1
			|| map_inf->ea > 1)
			return (0);
	}
	return (1);
}
