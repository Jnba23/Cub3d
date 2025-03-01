/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:45:14 by asayad            #+#    #+#             */
/*   Updated: 2025/03/01 10:46:09 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
