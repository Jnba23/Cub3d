/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:32:07 by asayad            #+#    #+#             */
/*   Updated: 2024/12/24 11:03:01 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_nd_fill_map(t_map **map_inf)
{
	int		i;
	int		j;
	char	**map;

	i = 1;
	j = 0;
	map = (*map_inf)->map_2d;
	while (map[i])
	{
		if (!check_pre_line(ft_strlen(map[i - 1]), map, i))
			return (ft_putendl_fd("Map not surrounded by walls !", 2), 0);
		if (!check_line(map_inf, i))
			return (ft_putendl_fd("Invalid map !", 2), 0);
		i++;
	}
	return (1);
}

int	check_pre_line(int pre_l, char **map_line, int idx)
{
	int	i;
	int	j;

	i = ft_strlen(map_line[idx]);
	j = i - (i - pre_l);
	if (i >= pre_l)
	{
		j--;
		if (map_line[idx][j] != '1' && map_line[idx - 1][j] != '1')
			return (0);
	}
	else if (i > 0 && i < pre_l)
	{
		i--;
		if (map_line[idx - 1][i] != '1' && map_line[idx][i] != '1')
			return (0);
	}
	return (1);
}

int	check_line(t_map **map_inf, int idx)
{
	int	i;
	char	**map;

	i = 0;
	map = (*map_inf)->map_2d;
	skip_spaces(map[idx], &i);
	if (!is_map_element(*map_inf, idx, i))
		return (0);
	while (map[idx][i])
	{
		if (map[idx][0] != '1' || map[idx][ft_strlen(map[idx]) - 1] != '1')
			return (ft_putendl_fd("Map not surrounded by walls !", 2), 0);
		if (!check_diff_dirs(map, idx, i))
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
		if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != 'N' && map[x][y] != 'S'
			&& map[x][y] != 'E' && map[x][y] != 'W')
			return (0);
		if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
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
	if (map[i] + j + 1 && map[i][j + 1] == ' ' && map[i][j - 1] == ' ')
	{
		if (i > ft_strlen(map[i - 1]) || (map + i + 1 && i > ft_strlen(map[i + 1])))
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
	int	pre_l;
	int	next_l;

	pre_l = ft_strlen(map[line - 1]);
	next_l = ft_strlen(map[line + 1]);
	if (map[line][c] == '0' || map[line][c] == 'N' || map[line][c] == 'S'
		|| map[line][c] == 'E' || map[line][c] == 'W')
	{
		if (map[line][c + 1] == ' ')
			return (0);
		if (c  >= ft_strlen(map[line - 1]))
			return (0);
		if (c  >= ft_strlen(map[line + 1]))
			return (0);
		if (line == 1)
		{
			if (map[line - 1][c] == '0' || map[line - 1][c] == ' ')
				return (0);
		}
		if (line == table_size(map) - 1)
		{
			puts("-------");
			puts(map[line]);
			if (map[line][c] == '0')
				return (0);
		}
	}
	return (1);
}
