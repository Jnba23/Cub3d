/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:57:51 by asayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:04:03 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	colors(t_color *clrs, char *rgb_s, int i)
{
	bool			a;
	unsigned int	val;

	if (i == 3)
		return (1);
	a = false;
	if (i == 0)
		*clrs = 0;
	val = ft_atoi(&rgb_s, &a);
	if (val == 0 && a == true)
		return (0);
	*clrs |= val << (2 - i) * 8;
	skip_spaces_ptr(&rgb_s);
	if (i < 2 && !ft_isdigit(*rgb_s))
		return (0);
	return (colors(clrs, rgb_s, i + 1));
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
			return (print_error("Map not surrounded by walls !"), 0);
		if (!map_char(s + i))
			return (print_error("Invalid character(s) !"), 0);
		j++;
		l = l->next;
	}
	return (1);
}

int	check_empty_lines(t_map *map_inf)
{
	t_list	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!map_inf->map)
		return (print_error("No map !"), 0);
	tmp = *map_inf->map;
	while (tmp)
	{
		if (is_empty((char *)tmp->content) || !tmp->next)
		{
			if (flag == 0)
				map_inf->map_size = i + 1;
			if (!check_rest_of_map(&tmp->next))
				return (0);
			flag = 1;
		}
		i++;
		tmp = tmp->next;
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
			return (print_error("Empty line(s) in the map !"), 0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_strcpy(char *src, char *dst)
{
	int	i;

	i = -1;
	if (!src || !dst)
		return ;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
}
