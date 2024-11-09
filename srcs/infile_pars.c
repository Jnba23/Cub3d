/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:15:59 by asayad            #+#    #+#             */
/*   Updated: 2024/11/06 15:05:21 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int ac, char **av)
{
	t_map	map_inf;

	if (ac == 2)
	{
		if (ft_strlen(av[1]) >= 4 && !ft_strcmp(av[1]
				+ (ft_strlen(av[1]) - 4), ".cub"))
		{
			initialize_map(&map_inf);
			if (!check_infile(av[1], &map_inf))
				return (1);
		}
		else
			ft_putendl_fd("Incompatible map !!", 2);
	}
	else
		ft_putendl_fd("too many or few args !", 2);
	return (1);
}

void	initialize_map(t_map *map_inf)
{
	map_inf->no = 0;
	map_inf->so = 0;
	map_inf->ea = 0;
	map_inf->we = 0;
	map_inf->ceiling = 0;
	map_inf->floor = 0;
	map_inf->map_in = false;
	map_inf->player_in = false;
}

t_list	*check_infile(char *in, t_map *map_inf)
{
	int		fd;
	char	*s;
	t_list	*in_list;

	in_list = NULL;
	fd = open(in, O_RDONLY, 0677);
	if (fd < 0)
		return (ft_putendl_fd(strerror(errno), 2), NULL);
	s = get_next_line(fd);
	while (s)
	{
		if (ft_strncmp(s, "NO", 2) && ft_strncmp(s, "SO", 2)
			&& ft_strncmp(s, "WE", 2) && ft_strncmp(s, "EA", 2))
			s = rm_spaces(s);
		ft_lstadd_back(&in_list, ft_lstnew(s));
		s = get_next_line(fd);
	}
	if (!check_if_valid_data(&in_list, map_inf))
		return (NULL); //free inlist
	return (in_list);
}

char	*rm_spaces(char *s)
{
	int		j;
	char	*r;

	j = ft_strlen(s) - 2;
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
		i = analyze_line(tmp, map_inf);
		if (!map_inf->map_in && i == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		if (!map_inf->map_in && (i == 2 || i == 3 || i == 4))
			return (0);
		if (map_inf->map_in)
			break ;
		tmp = tmp->next;
	}
	if (!map_analysis(map_inf) || !cnvrt_lst_2_map(map_inf))
		return (0);
	check_nd_fill_map(map_inf);
	return (1);
}