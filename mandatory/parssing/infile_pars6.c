/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:47:42 by asayad            #+#    #+#             */
/*   Updated: 2025/02/24 14:39:53 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_textures(t_map **map_inf)
{
	if ((*map_inf)->north)
	{
		mlx_delete_texture((*map_inf)->north);
		(*map_inf)->north = NULL;
	}
	if ((*map_inf)->south)
	{
		mlx_delete_texture((*map_inf)->south);
		(*map_inf)->south = NULL;
	}
	if ((*map_inf)->east)
	{
		mlx_delete_texture((*map_inf)->east);
		(*map_inf)->east = NULL;
	}
	if ((*map_inf)->west)
	{
		mlx_delete_texture((*map_inf)->west);
		(*map_inf)->west = NULL;
	}
}

int	check_clrs_struct(char *l)
{
	t_clr	vars;

	vars.comma_cnt = 0;
	vars.i = -1;
	while (l[++vars.i])
	{
		if (!ft_isdigit(l[vars.i]) && l[vars.i] != ',' && !ft_isspace(l[vars.i]))
			return (0);
		else if (ft_isspace(l[vars.i]))
		{
			if (!ft_isspace(l[vars.i + 1]) && l[vars.i] != ',')
				return (0);
			continue ;
		}
		else if (l[vars.i] == ',')
		{
			vars.comma_cnt++;
			if (l[vars.i + 1] && l[vars.i + 1] == ',')
				return (0);
		}
		// else
		// {
		// 	printf("I'm HERE\n");
		// 	return (0);
		// }
	}
	if (vars.comma_cnt != 2)
		return (0);
	return (1);
}

// int	check_clrs_struct(char *l)
// {
// 	t_clr	vars;

// 	vars.comma_cnt = 0;
// 	vars.nbr_cnt = 0;
// 	vars.i = -1;
// 	while (l[++vars.i])
// 	{
// 		if (ft_isdigit(l[vars.i]))
// 			vars.nbr_cnt++;
// 		else if (ft_isspace(l[vars.i]))
// 			continue ;
// 		else if (l[vars.i] == ',')
// 		{
// 			vars.comma_cnt++;
// 			if (vars.nbr_cnt == 0 || vars.nbr_cnt > 3)
// 				return (0);
// 			vars.nbr_cnt = 0;
// 		}
// 		else
// 			return (0);
// 	}
// 	if (vars.comma_cnt != 2)
// 		return (0);
// 	return (1);
// }

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
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
