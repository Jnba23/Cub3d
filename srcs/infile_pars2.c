/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:59:02 by asayad            #+#    #+#             */
/*   Updated: 2024/11/06 14:50:27 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	map_in(t_list *file_nd, t_map *map_inf)
{
	char	*l;

	l = (char *)file_nd->content;
	if (!is_empty(l))
	{
		if (!check_fst_line(l))
			return (0);
		map_inf->map_in = true;
		map_inf->map = &file_nd;
		return (1);
	}
	return (0);
}

int	check_fst_line(char *l)
{
	int	i;

	i = 0;
	while (i < ft_strlen(l))
	{
		if (l[i] == ' ')
			i++;
		else if (l[i] != '1')
		{
			ft_putendl_fd("Invalid map !", 2);
			return (0);
		}
		else if (l[i] == '1')
		{
			if (!check_rest_of_line(l + i))
			{
				ft_putendl_fd("Invalid map !", 2);
				return (0);
			}
			else
				break ;
		}
		i++;
	}
	return (1);
}

int	check_rest_of_line(char *l)
{
	int	i;

	i = 0;
	while (l[i])
	{
		if (l[i] != '1' && l[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

const char	*find_path(char *l)
{
	while (*l)
	{
		if (*l == '.' || *l == '/')
			return (ft_strdup(l, ft_strlen(l) - 2));
		l++;
	}
	return (NULL);
}

int	check_color(char *l, t_map *map_inf, char c)
{
	int		i;
	char	*red;
	char	*green;
	char	*blue;

	i = 1;
	green = NULL;
	blue = NULL;
	while (l[i] == ' ')
		i++;
	red = ft_strdup_c(l + i, ',');
	if (ft_strlen(l + i) >= ft_strlen(red) + 2)
		green = ft_strdup_c(l + i + ft_strlen(red) + 2, ',');
	if (ft_strlen(l + i) >= ft_strlen(red) + ft_strlen(green) + 4)
		blue = ft_strdup_c(l + i + ft_strlen(red) + ft_strlen(green) + 4, ',');
	if (!red || !green || !blue)
		return (0);
	if (!rgb(red, blue, green))
		return (free(red), free(green), free(blue), 0);
	if (c == 'f')
		return (cub_floor(map_inf, red, green, blue));
	if (c == 'c')
		return (ceiling(map_inf, red, green, blue));
	return (1);
}
