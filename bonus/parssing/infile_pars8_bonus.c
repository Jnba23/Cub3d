/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars8_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:53:42 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 19:03:29 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	east_west(char *l, t_map *map_inf, char *dir)
{
	if (!ft_strcmp(dir, "ea"))
	{
		map_inf->ea++;
		return (textures(l, &map_inf->east));
	}
	else if (!ft_strcmp(dir, "we"))
	{
		map_inf->we++;
		return (textures(l, &map_inf->west));
	}
	return (1);
}

int	textures(char *l, mlx_texture_t **direction)
{
	char	*s;
	char	*path;

	path = (char *)find_path(l);
	s = ft_strdup(path, ft_strlen(path) - 1);
	*direction = mlx_load_png(s);
	free(s);
	free(path);
	if (!*direction)
		return (print_error((char *)mlx_strerror(mlx_errno)), 0);
	return (1);
}

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
