/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:18:29 by asayad            #+#    #+#             */
/*   Updated: 2025/02/28 11:48:21 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_order(t_map *map_inf, char *s)
{
	if (!strcmp(s, "no"))
	{
		if (map_inf->ea != 0 || map_inf->so != 0
			|| map_inf->we != 0 || map_inf->no > 1)
			return (0);
	}
	if (!strcmp(s, "so"))
	{
		if (map_inf->no != 1 || (map_inf->ea != 0
				|| map_inf->we != 0 || map_inf->so > 1))
			return (0);
	}
	if (!strcmp(s, "we"))
	{
		if ((map_inf->no != 1 || map_inf->so != 1) || map_inf->ea != 0
			|| map_inf->we > 1)
			return (0);
	}
	if (!strcmp(s, "ea"))
	{
		if (map_inf->no != 1 || map_inf->so != 1 || map_inf->we != 1
			|| map_inf->ea > 1)
			return (0);
	}
	if (map_inf->ceiling != 0 || map_inf->floor != 0)
		return (0);
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
			return (free_table(vars.i, size), 0);
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
		if (!ft_isdigit(clr[i]) && !ft_isspace(clr[i]) && clr[i] != '+')
		{
			return (0);
		}
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

int	textures(char *l, mlx_texture_t **direction, t_map *map_inf, char *dir)
{
	char	*s;
	char	*path;

	if (!check_order(map_inf, dir))
		return (free_textures(map_inf),
			print_error("Wrong elment's order !"), 0);
	path = (char *)find_path(l);
	s = ft_strdup(path, ft_strlen(path) - 1);
	*direction = mlx_load_png(s);
	free(s);
	free(path);
	if (!*direction)
		return (free_textures(map_inf),
			print_error((char *)mlx_strerror(mlx_errno)), 0);
	return (1);
}
