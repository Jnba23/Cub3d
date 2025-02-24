/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:00:45 by asayad            #+#    #+#             */
/*   Updated: 2025/02/24 14:26:33 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	analyze_line(t_list **file_nd, t_map **map_inf)
{
	if (!(*map_inf)->map_in && is_empty((char *)((*file_nd)->content)))
		return (1);
	else if (!(*map_inf)->map_in && ((!ft_strncmp((char *)((*file_nd)->content),
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
	else if ((*map_inf)->map_in && is_empty((char *)((*file_nd)->content)))
		return (1);
	else if (!(*map_inf)->map_in && !map_in(file_nd, map_inf))
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

int	colors_nd_texture(char *l, t_map **map_inf)
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
		(*map_inf)->floor++;
		if (!check_color(l, map_inf, 'f'))
			return (ft_putendl_fd("Invalid colors !", 2), 0);
	}
	else if (!ft_strncmp(l, "C", 1))
	{
		(*map_inf)->ceiling++;
		if (!check_color(l, map_inf, 'c'))
			return (ft_putendl_fd("Invalid colors !", 2), 0);
	}
	return (1);
}

int	open_textures(char *l, t_map **map_inf, char *dir)
{
	if (!ft_strcmp(dir, "d"))
	{
		(*map_inf)->d++;
		return (textures(l, &(*map_inf)->door, map_inf));
	}
	if (!ft_strcmp(dir, "no"))
	{
		(*map_inf)->no++;
		return (textures(l, &(*map_inf)->north, map_inf));
	}
	if (!ft_strcmp(dir, "so"))
	{
		(*map_inf)->so++;
		return (textures(l, &(*map_inf)->south, map_inf));
	}
	if (!ft_strcmp(dir, "ea"))
	{
		(*map_inf)->ea++;
		return (textures(l, &(*map_inf)->east, map_inf));
	}
	if (!ft_strcmp(dir, "we"))
	{
		(*map_inf)->we++;
		return (textures(l, &(*map_inf)->west, map_inf));
	}
	return (0);
}

int	textures(char *l, mlx_texture_t **direction, t_map **map_inf)
{
	char	*s;
	char	*path;
	(void) map_inf;

	path = (char *)find_path(l);
	s = ft_strdup(path, ft_strlen(path) - 1);
	*direction = mlx_load_png(s);
	free(s);
	free(path);
	if (!*direction)
		return (/*free_textures(map_inf)*/
			printf("%s\n", mlx_strerror(mlx_errno)), 0);
	return (1);
}

void	free_textures(t_map **map_inf)
{
	if ((*map_inf)->north)
	{
		mlx_delete_texture((*map_inf)->north);
		(*map_inf)->north = NULL;
	}
	if ((*map_inf)->south)
	{
		mlx_delete_texture((*map_inf)->south);
		(*map_inf)->south = NULL;
	}
	if ((*map_inf)->east)
	{
		mlx_delete_texture((*map_inf)->east);
		(*map_inf)->east = NULL;
	}
	if ((*map_inf)->west)
	{
		mlx_delete_texture((*map_inf)->west);
		(*map_inf)->west = NULL;
	}
	if ((*map_inf)->door)
	{
		mlx_delete_texture((*map_inf)->door);
		(*map_inf)->door = NULL;
	}
}
