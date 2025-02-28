/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars6_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:37:04 by asayad            #+#    #+#             */
/*   Updated: 2025/02/28 11:36:32 by hmoukit          ###   ########.fr       */
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

size_t	ft_strlcpy_split(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	else
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	map_char(char *s)
{
	while (*s)
	{
		if (*s != '0' && *s != '1' && *s != 'N' && *s != 'S'
			&& *s != 'E' && *s != 'W' && *s != ' ' && *s != 'D')
			return (print_error("Invalid map data !"), 0);
		s++;
	}
	return (1);
}
