/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:57:51 by asayad            #+#    #+#             */
/*   Updated: 2024/11/06 10:29:54 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	rgb(char *red, char *green, char *blue)
{
	while (*red)
	{
		if (*red < '0' || *red > '9')
			return (0);
		red++;
	}
	while (*green)
	{
		if (*green < '0' || *green > '9')
			return (0);
		green++;
	}
	while (*blue)
	{
		if (*blue < '0' || *blue > '9')
			return (0);
		blue++;
	}
	return (1);
}

int	map_analysis(t_map *map_inf)
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
	l = *map_inf->map;
	while (l && j < map_inf->map_size - 1)
	{
		i = 0;
		s = (char *)l->content;
		while (s[i] == ' ')
			i++;
		if (s[i] != '1' || s[ft_strlen(s) - 1] != '1')
			return (0);
		if (!map_char(s + i))
			return (0);
		j++;
		l = l->next;
	}
	return (1);
}

int	map_elements(t_map *map_inf)
{
	printf("NO %d\n", map_inf->no);
	printf("SO %d\n", map_inf->so);
	printf("EA %d\n", map_inf->ea);
	printf("WE %d\n", map_inf->we);
	printf("F %d\n", map_inf->floor);
	printf("C %d\n", map_inf->ceiling);
	if (map_inf->ea != 1 || map_inf->we != 1 || map_inf->no != 1
		|| map_inf->so != 1 || map_inf->ceiling != 1 || map_inf->floor != 1)
		return (ft_putendl_fd("Missing or duplicate map data !", 2), 0);
	return (1);
}

int	check_empty_lines(t_map *map_inf)
{
	t_list	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	tmp = *map_inf->map;
	if (tmp)
	{
		while (tmp)
		{
			if (is_empty((char *)tmp->content) && tmp->next)
			{
				if (flag == 0)
					map_inf->map_size = i;
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
