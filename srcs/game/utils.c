/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:32:13 by asayad            #+#    #+#             */
/*   Updated: 2025/01/13 20:03:31 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	va_y_up(float va)
{
	if ((va >= 0 && va <= PI))
		return (0);
	return (1);
}

int	va_x_right(float va)
{
	if ((va >= 0 && va <= PI / 2) || (va >= (3 * PI) / 2.0 && va <= 2 * PI))
		return (1);
	return (0);
}

bool valid_ray_intersection(t_game *game, float hx, float hy)
{
	float 	a[3][2];
	int 	j;
	int		x_coo;
	int		y_coo;

	j = 0;
	a[0][0] = game->pl_y_pix + hy;
	a[0][1] = game->pl_x_pix + hx;
	a[1][0] = game->pl_y_pix + hy + 1.0f;
	a[1][1] = game->pl_x_pix + hx + 1.0f;
	a[2][0] = game->pl_y_pix + hy - 1.0f;
	a[2][1] = game->pl_x_pix + hx - 1.0f;
	while (j < 3)
	{
		y_coo = (int)floor(a[j][0] * REV_TILE);
		x_coo = (int)floor(a[j][1] * REV_TILE);
		if (y_coo < 0 || y_coo > game->map_inf->map_height || x_coo < 0
			|| x_coo > ft_strlen(game->map[y_coo]))
			return (0);
		if (game->map[y_coo][x_coo] == '1')
			return (0) ;
		j++;
	}
	if (y_coo < 0 || y_coo >= game->map_inf->map_height || x_coo < 0 || x_coo >= ft_strlen(game->map[y_coo]))
		return (0);

	// Check for wall at the current position
	if (game->map[y_coo][x_coo] == '1')
		return (0);
	return (1);
    // return (floor((game->pl_y_pix + hy) / TILE_SIZE) >= 0 &&
    //         floor((game->pl_y_pix + hy) / TILE_SIZE) < game->map_inf->map_height
	// 		&& floor((game->pl_x_pix + hx) / TILE_SIZE) >= 0
	// 		&& floor((game->pl_x_pix + hx) / TILE_SIZE)
	// 		< ft_strlen(game->map[(int)floor((game->pl_y_pix + hy) / TILE_SIZE)])
	// 		&& game->map[(int)floor((game->pl_y_pix + hy) / TILE_SIZE)]
    //         [(int)floor((game->pl_x_pix + hx) / TILE_SIZE)] != '1');
}

void	normalize_ang(float *alpha, float *max_ang)
{
	// if (*alpha != 0 && *alpha != PI / 2 && *alpha != PI
	// 	&& *alpha != 3 * PI / 2)
	// {
		if (*alpha < 0)
		{
			*alpha = fmod(*alpha, 2 * PI) + 2 * PI;
			*max_ang += 2 * PI;
		}
		else if (*alpha > 2 * PI)
			*alpha -= 2 * PI;
	// }
}

// void	reset_mvs_indic(t_game *game)
// {
// 	game->pl_inf->turn_dir = 0;
// 	game->pl_inf->walk_dir = 0;
// 	game->pl_inf->turn_dir = 0;
// }
