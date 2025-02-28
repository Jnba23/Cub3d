/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:15:59 by asayad            #+#    #+#             */
/*   Updated: 2025/02/28 11:06:49 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	initialize_map(t_map *map_inf)
{
	map_inf->no = 0;
	map_inf->north = 0;
	map_inf->so = 0;
	map_inf->south = 0;
	map_inf->ea = 0;
	map_inf->east = 0;
	map_inf->we = 0;
	map_inf->west = 0;
	map_inf->ceiling = 0;
	map_inf->floor = 0;
	map_inf->map_in = false;
	map_inf->map_size = 0;
	map_inf->player_in = false;
	map_inf->map_2d = 0;
}

int	check_infile(char *in, t_map *map_inf)
{
	int		fd;
	char	*s;
	t_list	*in_list;

	in_list = NULL;
	fd = open(in, O_RDONLY, 0677);
	if (fd < 0)
		return (print_error(strerror(errno)), 0);
	s = get_next_line(fd);
	while (s)
	{
		if (ft_strncmp(s, "NO ", 3) && ft_strncmp(s, "SO ", 3)
			&& ft_strncmp(s, "WE ", 3) && ft_strncmp(s, "EA ", 3))
			s = rm_spaces(s);
		ft_lstadd_back(&in_list, ft_lstnew(s));
		s = get_next_line(fd);
	}
	close(fd);
	if (!check_if_valid_data(&in_list, map_inf))
		return (free_in_list(in_list), 0);
	free_in_list(in_list);
	add_map_inf(map_inf);
	return (1);
}

char	*rm_spaces(char *s)
{
	int		j;
	char	*r;

	if (s[ft_strlen(s) - 1] == '\n')
		j = ft_strlen(s) - 2;
	else
		j = ft_strlen(s) - 1;
	while (j >= 0 && s[j] == ' ')
		j--;
	r = ft_strdup(s, j);
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (r);
}

int	check_if_valid_data(t_list **in_list, t_map *map_inf)
{
	t_list	*tmp;
	int		i;

	tmp = *in_list;
	while (tmp)
	{
		i = analyze_line(&tmp, map_inf);
		if (!map_inf->map_in && i == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		if (!map_inf->map_in && (i == 2 || i == 3))
			return (free_textures(map_inf), 0);
		if (map_inf->map_in)
			break ;
		tmp = tmp->next;
	}
	if (!map_analysis(map_inf) || !cnvrt_lst_2_map(map_inf))
		return (free_textures(map_inf), 0);
	if (!map_inf->map_in || !check_nd_fill_map(map_inf))
		return (free_textures(map_inf), free_table(map_inf->map_2d,
				map_inf->map_size), 0);
	return (1);
}

void	add_map_inf(t_map *map_inf)
{
	char	**map;
	int		i;
	int		tmp;

	map = map_inf->map_2d;
	i = 0;
	map_inf->map_width = ft_strlen(map[i]);
	while (map[i])
	{
		tmp = ft_strlen(map[i]);
		if (map_inf->map_width < tmp)
			map_inf->map_width = tmp;
		i++;
	}
	map_inf->map_height = table_size(map_inf->map_2d);
}
