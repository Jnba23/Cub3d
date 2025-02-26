/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars6_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:37:04 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 16:33:23 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	check_color(char *l, t_map *map_inf, char c)
{
	int		i;
	color	clrs;

	i = 1;
	skip_spaces(l, &i);
	if (!check_clrs_struct(l + i))
		return (0);
	if (!colors(&clrs, l + i, 0))
		return (0);
	if (c == 'f')
	{
		map_inf->red_f = clrs >> 16 & 0xFF;
		map_inf->green_f = clrs >> 8 & 0xFF;
		map_inf->blue_f = clrs & 0xFF;
	}
	if (c == 'c')
	{
		map_inf->red_c = clrs >> 16 & 0xFF;
		map_inf->green_c = clrs >> 8 & 0xFF;
		map_inf->blue_c = clrs & 0xFF;
	}
	return (1);
}

int	check_clrs_struct(char *l)
{
	t_clr	vars;
	int		size;

	vars.idx = 0;
	vars.i = ft_split(l, ',');
	size = table_size(vars.i);
	if (size != 3)
		return (0);
	if (!check_commas(l))
		return (free_table(vars.i, size), 0);
	while (vars.i[vars.idx])
	{
		if (!valid_color(vars.i[vars.idx]))
			return (0);
		vars.idx++;
	}
	free_table(vars.i, size);
	return (1);
}

int	valid_color(char *clr)
{
	int		i;
	bool	space;

	i = -1;
	space = false;
	while (clr[++i])
	{
		if (!ft_isdigit(clr[i]) && !ft_isspace(clr[i]))
			return (0);
		if (ft_isspace(clr[i]))
			space = true;
		if (ft_isdigit(clr[i] && space))
			return (0);
	}
	return (1);
}

int	check_commas(char *l)
{
	int	i;
	int	comma_cnt;

	i = -1;
	comma_cnt = 0;
	while (l[++i])
	{
		if (l[i] == ',')
			comma_cnt++;
	}
	if (comma_cnt != 2)
		return (0);
	return (1);
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
