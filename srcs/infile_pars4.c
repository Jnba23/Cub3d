/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:54:40 by asayad            #+#    #+#             */
/*   Updated: 2024/11/06 13:37:04 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	cub_floor(t_map *map_inf, char *red, char *green, char *blue)
{
	map_inf->red_f = ft_atoi(red);
	map_inf->green_f = ft_atoi(green);
	map_inf->blue_f = ft_atoi(blue);
	if (map_inf->red_f > 255 || map_inf->green_f > 255 || map_inf->blue_f > 255)
		return (0);
	return (1);
}

int	ceiling(t_map *map_inf, char *red, char *green, char *blue)
{
	map_inf->red_c = ft_atoi(red);
	map_inf->green_c = ft_atoi(green);
	map_inf->blue_c = ft_atoi(blue);
	if (map_inf->red_c >= 255 || map_inf->green_c >= 255
		|| map_inf->blue_c >= 255)
		return (0);
	return (1);
}

int	cnvrt_lst_2_map(t_map *map_inf)
{
	char	*l;
	int		j;
	t_list	*tmp;

	j = 0;
	tmp = *map_inf->map;
	map_inf->map_2d = malloc(sizeof(char *) * (map_inf->map_size + 1));
	if (!map_inf->map_2d)
		return (ft_putendl_fd("Malloc failed !", 2), 0);
	while (tmp && j < map_inf->map_size)
	{
		l = (char *)tmp->content;
		map_inf->map_2d[j] = malloc (sizeof(char) * (ft_strlen(l) + 1));
		if (!map_inf->map_2d[j])
			return(free_table(map_inf->map_2d, j), 0);
		ft_strcpy(l, map_inf->map_2d[j]);
		tmp = tmp->next;
		j++;
	}
	map_inf->map_2d[j] = NULL;
	return (1);
}

void	free_table(char **map, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(map[i++]);
	free(map);
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
