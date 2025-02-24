/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:00:45 by asayad            #+#    #+#             */
/*   Updated: 2025/02/24 16:00:40 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	analyze_line(t_list **file_nd, t_map **map_inf)
{
	if (!(*map_inf)->map_in && is_empty((char *)((*file_nd)->content)))
		return (1);
	else if (!(*map_inf)->map_in && (!ft_strncmp((char *)((*file_nd)->content),
			"NO", 2)
		|| !ft_strncmp((char *)((*file_nd)->content), "SO", 2)
		|| !ft_strncmp((char *)((*file_nd)->content), "WE", 2)
		|| !ft_strncmp((char *)((*file_nd)->content), "EA", 2)
		|| !ft_strncmp((char *)((*file_nd)->content), "F", 1)
		|| !ft_strncmp((char *)((*file_nd)->content), "C", 1)))
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
	else if (!ft_strncmp(l, "F", 1))
	{
		(*map_inf)->floor++;
		if ((*map_inf)->ceiling != 0)
			return (free_textures(map_inf), ft_putendl_fd("Wrong element's order !", 2), 0);
		if (!check_color(l, map_inf, 'f'))
			return (ft_putendl_fd("Invalid colors !", 2), 0);
	}
	else if (!ft_strncmp(l, "C", 1))
	{
		(*map_inf)->ceiling++;
		if ((*map_inf)->floor != 1)
			return (free_textures(map_inf), ft_putendl_fd("Wrong element's order !", 2), 0);	
		if (!check_color(l, map_inf, 'c'))
			return (ft_putendl_fd("Invalid colors !", 2), 0);
	}
	return (1);
}

int	open_textures(char *l, t_map **map_inf, char *dir)
{
	if (!ft_strcmp(dir, "no"))
	{
		(*map_inf)->no++;
		return (textures(l, &(*map_inf)->north, map_inf, "no"));
	}
	if (!ft_strcmp(dir, "so"))
	{
		(*map_inf)->so++;
		return (textures(l, &(*map_inf)->south, map_inf, "so"));
	}
	if (!ft_strcmp(dir, "ea"))
	{
		(*map_inf)->ea++;
		return (textures(l, &(*map_inf)->east, map_inf, "ea"));
	}
	if (!ft_strcmp(dir, "we"))
	{
		(*map_inf)->we++;
		return (textures(l, &(*map_inf)->west, map_inf, "we"));
	}
	return (0);
}

int	textures(char *l, mlx_texture_t **direction, t_map **map_inf, char *dir)
{
	char	*s;
	char	*path;

	if (!check_order(map_inf, dir))
		return (free_textures(map_inf),
			ft_putendl_fd("Wrong elment's order !", 2), 0);
	path = (char *)find_path(l);
	s = ft_strdup(path, ft_strlen(path) - 1);
	*direction = mlx_load_png(s);
	free(s);
	free(path);
	if (!*direction)
		return (free_textures(map_inf),ft_putendl_fd(
				(char *)mlx_strerror(mlx_errno), 2), 0);
	return (1);
}

int	check_order(t_map **map_inf, char *s)
{
	if (!strcmp(s, "no"))
	{
		if ((*map_inf)->ea != 0 || (*map_inf)->so != 0
			|| (*map_inf)->we != 0)
			return (0);
	}
	if (!strcmp(s, "so"))
	{
		if ((*map_inf)->no != 1 || ((*map_inf)->ea != 0
			|| (*map_inf)->we != 0))
			return (0);
	}
	if (!strcmp(s, "we"))
	{
		if (((*map_inf)->no != 1 || (*map_inf)->so != 1) || (*map_inf)->ea != 0)
			return (0);
	}
	if (!strcmp(s, "ea"))
	{
		if ((*map_inf)->no != 1 || (*map_inf)->so != 1 || (*map_inf)->we != 1)
			return (0);
	}
	if ((*map_inf)->ceiling != 0 || (*map_inf)->floor != 0)
		return (0);
	return (1);
}
