/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_pars6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:47:42 by asayad            #+#    #+#             */
/*   Updated: 2025/02/20 11:51:32 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_textures(t_map **map_inf)
{
	if ((*map_inf)->north)
		mlx_delete_texture((*map_inf)->north);
	if ((*map_inf)->south)
		mlx_delete_texture((*map_inf)->south);
	if ((*map_inf)->east)
		mlx_delete_texture((*map_inf)->east);
	if ((*map_inf)->west)
		mlx_delete_texture((*map_inf)->west);
}

int	check_clrs_struct(char *l)
{
	t_clr	vars;

	vars.comma_cnt = 0;
	vars.nbr_cnt = 0;
	vars.i = -1;
	while (l[++vars.i])
	{
		if (ft_isdigit(l[vars.i]))
			vars.nbr_cnt++;
		else if (ft_isspace(l[vars.i]))
			continue ;
		else if (l[vars.i] == ',')
		{
			vars.comma_cnt++;
			if (vars.nbr_cnt == 0 || vars.nbr_cnt > 3)
				return (0);
			vars.nbr_cnt = 0;
		}
		else
			return (0);
	}
	if (vars.comma_cnt != 2)
		return (0);
	return (1);
}

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
