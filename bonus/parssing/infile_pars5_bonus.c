/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars5_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:32:07 by asayad            #+#    #+#             */
/*   Updated: 2025/02/28 11:53:40 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	check_nd_fill_map(t_map *map_inf)
{
	int		i;
	char	**map;

	i = 1;
	map = map_inf->map_2d;
	while (map[i])
	{
		if (ft_strlen(map[i]) == 0)
		{
			i++;
			continue ;
		}
		if (!check_pre_line(map, i))
			return (print_error("Map not surrounded by walls !"), 0);
		if (!check_line(map_inf, i))
			return (print_error("Invalid map !"), 0);
		i++;
	}
	if (!map_inf->player_in)
		return (print_error("No Player !"), 0);
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

int	check_line(t_map *map_inf, int idx)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = map_inf->map_2d;
	skip_spaces(map[idx], &i);
	j = i;
	if (!is_map_element(map_inf, idx, i))
		return (0);
	while (map[idx][i])
	{
		if (map[idx][j] != '1' || map[idx][ft_strlen(map[idx]) - 1] != '1')
			return (print_error("Map not surrounded by walls !"), 0);
		if (!check_diff_dirs(map, idx, i))
			return (0);
		i++;
	}
	return (1);
}
