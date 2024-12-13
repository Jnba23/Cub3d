/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:57:51 by asayad            #+#    #+#             */
/*   Updated: 2024/11/16 16:09:17 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

color	colors(char *rgb_s, int i)
{
	color	clrs;
	bool	a;

	if (i == 3)
		return (0);
	// if (!ft_isdigit(*rgb_s) && i < )
	a = false;
	clrs = ft_atoi(&rgb_s, &a);
	skip_spaces_ptr(&rgb_s);
	if (!ft_isdigit(*rgb_s) || a || (a && clrs == 0))
		return (0xFFFFFFFF);
	return ((clrs << (2 - i) * 8) & colors(rgb_s, i + 1));
}

int	map_analysis(t_map **map_inf)
{
	t_list	*l;
	char	*s;
	int		i;
	int		j;
	
	j = 0;
	if (!map_elements(map_inf))
		return (0);
	if (!check_empty_lines(map_inf))
		return (0);
	l = *(*map_inf)->map;
	while (l && j < (*map_inf)->map_size - 1)
	{
		i = 0;
		s = (char *)l->content;
		while (s[i] == ' ')
			i++;
		if (s[i] != '1' || s[ft_strlen(s) - 1] != '1')
			return (ft_putendl_fd("Map not surrounded by walls !", 2), 0);
		if (!map_char(s + i))
			return (ft_putendl_fd("Invalid character(s) !", 2), 0);
		j++;
		l = l->next;
	}
	return (1);
}

int	map_elements(t_map **map_inf)
{
	printf("NO %d\n", (*map_inf)->no);
	printf("SO %d\n", (*map_inf)->so);
	printf("EA %d\n", (*map_inf)->ea);
	printf("WE %d\n", (*map_inf)->we);
	printf("F %d\n", (*map_inf)->floor);
	printf("C %d\n", (*map_inf)->ceiling);
	if ((*map_inf)->ea != 1 || (*map_inf)->we != 1 || (*map_inf)->no != 1
		|| (*map_inf)->so != 1 || (*map_inf)->ceiling != 1 || (*map_inf)->floor != 1)
		return (ft_putendl_fd("Missing or duplicate map data !", 2), 0);
	return (1);
}

int	check_empty_lines(t_map **map_inf)
{
	t_list	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	tmp = *(*map_inf)->map;
	if (tmp)
	{
		while (tmp)
		{
			if (is_empty((char *)tmp->content) || !tmp->next)
			{
				if (flag == 0)
					(*map_inf)->map_size = i + 1;
				if (!check_rest_of_map(&tmp->next))
					return (0);
				flag = 1;
			}
			i++;
			tmp = tmp->next;
		}
	}
	return (1);
}

int	check_rest_of_map(t_list **map)
{
	t_list	*tmp;
	
	tmp = *map;
	while (tmp)
	{
		if (!is_empty((char *)tmp->content))
			return (ft_putendl_fd("Empty line(s) in the map !", 2), 0);
		tmp = tmp->next;
	}
	return (1);
}

//0, 1, N, S, E, W, ' '
int	map_char(char *s)
{
	while (*s)
	{
		if (*s != '0' && *s != '1' && *s != 'N' && *s != 'S'
			&& *s != 'E' && *s != 'W' && *s != ' ')
			return (ft_putendl_fd("Invalid map data !", 2), 0);
		s++;
	}
	return (1);
}
