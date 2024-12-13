/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:59:02 by asayad            #+#    #+#             */
/*   Updated: 2024/11/20 20:41:22 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	map_in(t_list **file_nd, t_map **map_inf)
{
	char	*l;

	l = (char *)((*file_nd)->content);
	if (!is_empty(l))
	{
		if (!check_fst_line(*file_nd))
			return (0);
		(*map_inf)->map_in = true;
		(*map_inf)->map = file_nd;
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
		if (((char *)(l->content))[i] == ' ')
			i++;
		else if (((char *)(l->content))[i] != '1')
		{
			ft_putendl_fd("Invalid map !", 2);
			return (0);
		}
		else if (((char *)(l->content))[i] == '1')
		{
			if (!check_rest_of_line(((char *)(l->content)) + i, l))
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

int	check_color(char *l, t_map **map_inf, char c)
{
	int		i;
	color	clrs;

	i = 1;
	skip_spaces(l, &i);
	clrs = colors(l + i, 0);
	if (clrs == 0xFFFFFFFF)
		return (0);
	if (c == 'f')
	{
		(*map_inf)->red_f = clrs >> 16 & 0xFF;
		(*map_inf)->green_f = clrs >> 8 & 0xFF;
		(*map_inf)->blue_f = clrs & 0xFF;
	}
	if (c == 'c')
	{
		(*map_inf)->red_c = clrs >> 16 & 0xFF;
		(*map_inf)->green_c = clrs >> 8 & 0xFF;
		(*map_inf)->blue_c = clrs & 0xFF;
	}
	return (1);
}
