/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars6_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:37:04 by asayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:05:53 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	free_textures(t_map *map_inf)
{
	if (map_inf->north)
	{
		mlx_delete_texture(map_inf->north);
		map_inf->north = NULL;
	}
	if (map_inf->south)
	{
		mlx_delete_texture(map_inf->south);
		map_inf->south = NULL;
	}
	if (map_inf->east)
	{
		mlx_delete_texture(map_inf->east);
		map_inf->east = NULL;
	}
	if (map_inf->west)
	{
		mlx_delete_texture(map_inf->west);
		map_inf->west = NULL;
	}
	if (map_inf->door)
	{
		mlx_delete_texture(map_inf->door);
		map_inf->door = NULL;
	}
}

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
