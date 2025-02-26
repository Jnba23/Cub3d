/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:00:45 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 17:54:37 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	analyze_line(t_list **file_nd, t_map *map_inf)
{
	if (!map_inf->map_in && is_empty((char *)((*file_nd)->content)))
		return (1);
	else if (!map_inf->map_in && ((!ft_strncmp((char *)((*file_nd)->content),
				"NO", 2)
			|| !ft_strncmp((char *)((*file_nd)->content), "SO", 2)
		|| !ft_strncmp((char *)((*file_nd)->content), "WE", 2)
			|| !ft_strncmp((char *)((*file_nd)->content), "EA", 2)
			|| !ft_strncmp((char *)((*file_nd)->content), "F", 1)
			|| !ft_strncmp((char *)((*file_nd)->content), "C", 1))
			|| !ft_strncmp((char *)((*file_nd)->content), "D", 1)))
	{
		if (!colors_nd_texture((char *)((*file_nd)->content), map_inf))
			return (2);
	}
	else if (map_inf->map_in && is_empty((char *)((*file_nd)->content)))
		return (1);
	else if (!map_inf->map_in && !map_in(file_nd, map_inf))
		return (3);
	return (0);
}

int	is_empty(char *l)
{
	int	i;

	i = 0;
	if (!l || !*l || !ft_strcmp(l, "\n"))
		return (1);
	while (l[i] == ' ')
		i++;
	if (i == ft_strlen(l))
		return (1);
	return (0);
}

int	colors_nd_texture(char *l, t_map *map_inf)
{
	if (!ft_strncmp(l, "NO", 2))
		return (open_textures(l, map_inf, "no"));
	else if (!ft_strncmp(l, "SO", 2))
		return (open_textures(l, map_inf, "so"));
	else if (!ft_strncmp(l, "WE", 2))
		return (open_textures(l, map_inf, "we"));
	else if (!ft_strncmp(l, "EA", 2))
		return (open_textures(l, map_inf, "ea"));
	else if (!ft_strncmp(l, "D", 1))
		return (open_textures(l, map_inf, "d"));
	else if (!ft_strncmp(l, "F", 1))
	{
		map_inf->floor++;
		if (!check_color(l, map_inf, 'f'))
			return (print_error("Invalid colors !"), 0);
	}
	else if (!ft_strncmp(l, "C", 1))
	{
		map_inf->ceiling++;
		if (!check_color(l, map_inf, 'c'))
			return (print_error("Invalid colors !"), 0);
	}
	return (1);
}

int	open_textures(char *l, t_map *map_inf, char *dir)
{
	if (!ft_strcmp(dir, "d"))
	{
		map_inf->d++;
		return (textures(l, &map_inf->door));
	}
	if (!ft_strcmp(dir, "no") || !ft_strcmp(dir, "so"))
		return (north_south(l, map_inf, dir));
	if (!ft_strcmp(dir, "ea") || !ft_strcmp(dir, "we"))
		return (east_west(l, map_inf, dir));
	return (0);
}

int	north_south(char *l, t_map *map_inf, char *dir)
{
	if (!ft_strcmp(dir, "no"))
	{
		map_inf->no++;
		return (textures(l, &map_inf->north));
	}
	else if (!ft_strcmp(dir, "so"))
	{
		map_inf->so++;
		return (textures(l, &map_inf->south));
	}
	return (1);
}
