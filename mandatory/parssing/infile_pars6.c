/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:47:42 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 13:05:16 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

//0, 1, N, S, E, W, ' '
int	map_char(char *s)
{
	while (*s)
	{
		if (*s != '0' && *s != '1' && *s != 'N' && *s != 'S'
			&& *s != 'E' && *s != 'W' && *s != ' ')
			return (print_error("Invalid map data !"), 0);
		s++;
	}
	return (1);
}
