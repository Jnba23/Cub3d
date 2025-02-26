/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars4_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:54:40 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 13:44:19 by asayad           ###   ########.fr       */
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
