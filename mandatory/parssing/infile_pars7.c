/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:54:08 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 11:14:21 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
		if (map[x][y] != '0' && map[x][y] != '1' && map[x][y]
			!= 'N' && map[x][y] != 'S'
			&& map[x][y] != 'E' && map[x][y] != 'W')
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
	if (map[i] + j + 1 && map[i][j + 1] == ' ' && map[i][j - 1] == ' ')
	{
		if (i > ft_strlen(map[i - 1]) || (map + i + 1 && i
				> ft_strlen(map[i + 1])))
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
			if (map[line][c] == '0')
				return (0);
		}
	}
	return (1);
}
