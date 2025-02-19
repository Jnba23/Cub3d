/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars5_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:32:07 by asayad            #+#    #+#             */
/*   Updated: 2025/02/19 19:08:43 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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
	return (1);
}

int	check_pre_line(char **map_line, int idx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

int	ones_nd_spaces(char *l, int i)
{
	while (l[i])
	{
		if (l[i] != '1' && l[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_element(t_map *map_inf, int x, int y)
{
	char	**map;

	map = map_inf->map_2d;
	while (map[x][y])
	{
		if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != 'N'
			&& map[x][y] != 'S' && map[x][y] != 'E' && map[x][y] != 'W'
			&& map[x][y] != 'D')
			return (0);
		if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E'
			|| map[x][y] == 'W')
		{
			if (map_inf->player_in)
				return (0);
			map_inf->player_in = true;
			map_inf->pl_dir = map[x][y];
			map_inf->p_pos_y = x;
			map_inf->p_pos_x = y;
		}
		y++;
	}
	return (1);
}

int	check_player(char **map, int i, int j)
{
	if (map[i] + j + 1 && map[i][j + 1] == ' '
		&& map[i][j - 1] == ' ')
	{
		if (i > ft_strlen(map[i - 1])
			|| (map + i + 1 && i > ft_strlen(map[i + 1])))
			return (0);
	}
	return (1);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] != ' ')
			break ;
		(*i)++;
	}
}

int	check_diff_dirs(char **map, int line, int c)
{
	if (map[line][c] == '0' || map[line][c] == 'N' || map[line][c] == 'S'
		|| map[line][c] == 'E' || map[line][c] == 'W')
	{
		if (map[line][c + 1] == ' ')
			return (0);
		if (c >= ft_strlen(map[line - 1]))
			return (0);
		if (c >= ft_strlen(map[line + 1]))
			return (0);
		if (line == 1)
		{
			if (map[line - 1][c] == '0' || map[line - 1][c] == ' ')
				return (0);
		}
		if (line == table_size(map) - 1)
		{
			puts(map[line]);
			if (map[line][c] == '0')
				return (0);
		}
	}
	return (1);
}
