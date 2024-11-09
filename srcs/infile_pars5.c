/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:32:07 by asayad            #+#    #+#             */
/*   Updated: 2024/11/09 16:45:17 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_nd_fill_map(t_map *map_inf)
{
	int		i;
	int		j;
	char	**map;

	i = 1;
	j = 0;
	map = map_inf->map_2d;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (ft_putendl_fd("Map not surrounded by walls !", 2), 0);
		if (!check_next_line(ft_strlen(map[i - 1]), map, i))
			return (ft_putendl_fd("Map not surrounded by walls !", 2), 0);
		i++;
	}
	return (0);
}

int	check_next_line(int pre_l, char **map_line, int idx)
{
	int	i;

	i = ft_strlen(map_line[idx]);
	if (i > pre_l)
	{
		pre_l--;
		while (map_line[idx][pre_l])
		{
			if (map_line[idx][pre_l] != '1')
				return (0);
			pre_l++;
		}
	}
	else if (i < pre_l)
	{
		i--;
		while (map_line[idx - 1][i])
		{
			if (map_line[idx - 1][i] != '1')
			{
				printf("%s\n", map_line[idx - 1]);
				printf("%s\n", map_line[idx]);
				return (0);
			}
			i++;
		}
	}
	return (1);
}