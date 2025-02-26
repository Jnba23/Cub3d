/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:59:02 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 13:38:46 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	map_in(t_list **file_nd, t_map *map_inf)
{
	char	*l;

	l = (char *)((*file_nd)->content);
	if (!is_empty(l))
	{
		if (!check_fst_line(*file_nd))
			return (0);
		map_inf->map_in = true;
		map_inf->map = file_nd;
		return (1);
	}
	return (0);
}

int	check_fst_line(t_list *l)
{
	int		i;

	i = 0;
	while (i < ft_strlen((char *)(l->content)))
	{
		if (((char *)(l->content))[i] == ' '
			|| ((char *)(l->content))[i] != '1')
		{
			print_error("Invalid map !");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_rest_of_line(char *c, t_list *l)
{
	int	i;
	int	j;

	i = 0;
	if (l->next)
	{
		j = ft_strlen(c);
		if (j > ft_strlen((char *)l->next->content))
			j = ft_strlen((char *)l->next->content);
		while (i < j)
		{
			if (c[i] != '1' && c[i] != ' ' && c[i] != '0')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
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

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
