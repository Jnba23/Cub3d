/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:32:07 by asayad            #+#    #+#             */
/*   Updated: 2025/02/24 14:52:01 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_nd_fill_map(t_map **map_inf)
{
	int		i;
	char	**map;

	i = 1;
	map = (*map_inf)->map_2d;
	while (map[i])
	{
		if (!check_pre_line(map, i))
			return (ft_putendl_fd("Map not surrounded by walls !", 2), 0);
		if (!check_line(map_inf, i))
			return (ft_putendl_fd("Invalid map !", 2), 0);
		i++;
	}
	if (!(*map_inf)->player_in)
		return (ft_putendl_fd("No Player !", 2), 0);
	return (1);
}

int	check_pre_line(char **map_line, int idx)
{
	if (!check_begin_lines(map_line, idx))
		return (0);
	if (!check_end_lines(map_line, idx))
		return (0);
	return (1);
}

int	check_begin_lines(char **map, int idx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	skip_spaces(map[idx], &i);
	skip_spaces(map[idx - 1], &j);
	if (i == j && (map[idx][i] != '1' || map[idx - 1][i] != '1'))
		return (0);
	if (i < j)
	{
		if (j - 1 < ft_strlen(map[idx]) && (map[idx - 1][j] != '1'
			|| map[idx][j - 1] != '1'))
			return (0);
	}
	else if (i > j)
	{
		if (i - 1 < ft_strlen(map[idx - 1]) && (map[idx][i] != '1'
			|| map[idx - 1][i - 1] != '1'))
			return (0);
	}
	return (1);
}

int	check_end_lines(char **map, int idx)
{
	int	i;
	int	j;

	i = ft_strlen(map[idx]);
	j = ft_strlen(map[idx - 1]);
	if (i == j && (map[idx][i - 1] != '1' || map[idx - 1][i - 1] != '1'))
		return (0);
	if (i < j)
	{
		if (map[idx][i - 1] != '1' || map[idx - 1][i] != '1'
			|| !ones_nd_spaces(map[idx - 1], i + 1))
			return (0);
	}
	else if (i > j)
	{
		if (map[idx - 1][j - 1] != '1' || map[idx][j] != '1'
			|| !ones_nd_spaces(map[idx], j + 1))
			return (0);
	}
	return (1);
}

int	check_line(t_map **map_inf, int idx)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = (*map_inf)->map_2d;
	skip_spaces(map[idx], &i);
	j = i;
	if (!is_map_element(*map_inf, idx, i))
		return (0);
	while (map[idx][i])
	{
		if (map[idx][j] != '1' || map[idx][ft_strlen(map[idx]) - 1] != '1')
			return (ft_putendl_fd("Map not surrounded by walls !", 2), 0);
		if (!check_diff_dirs(map, idx, i))
			return (0);
		i++;
	}
	return (1);
}
