/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars4_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:54:40 by asayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:04:53 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	cnvrt_lst_2_map(t_map *map_inf)
{
	char	*l;
	int		j;
	t_list	*tmp;

	j = 0;
	tmp = *map_inf->map;
	if (map_inf->map_size == 0)
		return (print_error("No Map !"), 0);
	map_inf->map_2d = malloc(sizeof(char *) * (map_inf->map_size + 1));
	if (!map_inf->map_2d)
		return (print_error("Malloc failed !"), 0);
	while (tmp && j < map_inf->map_size)
	{
		l = (char *)tmp->content;
		map_inf->map_2d[j] = malloc (sizeof(char) * (ft_strlen(l) + 1));
		if (!map_inf->map_2d[j])
			return (free_table(map_inf->map_2d, j), 0);
		ft_strcpy(l, map_inf->map_2d[j]);
		tmp = tmp->next;
		j++;
	}
	map_inf->map_2d[j] = NULL;
	return (1);
}

void	free_table(char **table, int j)
{
	int		i;

	i = 0;
	while (i < j)
		free(table[i++]);
	free(table);
}

size_t	ft_strlcpy_split(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	else
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	map_char(char *s)
{
	while (*s)
	{
		if (*s != '0' && *s != '1' && *s != 'N' && *s != 'S'
			&& *s != 'E' && *s != 'W' && *s != ' ' && *s != 'D')
			return (print_error("Invalid map data !"), 0);
		s++;
	}
	return (1);
}
