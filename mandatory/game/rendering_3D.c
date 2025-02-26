/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:20:42 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 13:34:23 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calculate_ray_data(t_game *game, int i, float angle_beta, float min_d)
{
	int	wall_center;

	game->rays[i].d *= cos(angle_beta);
	if (game->rays[i].d < min_d)
		game->rays[i].d = min_d;
	if (!cos(angle_beta) || !game->rays[i].d)
		game->rays[i].d = 1;
	game->rays[i].wall_h = ((float)TILE_SIZE / (float)game->rays[i].d)
		* ((SCREEN_WIDTH / 2) / tan(deg2rad(FOV / 2)));
	wall_center = SCREEN_HEIGHT / 2;
	game->rays[i].top_pix = wall_center - (game->rays[i].wall_h / 2);
	game->rays[i].bott_pix = wall_center + (game->rays[i].wall_h / 2);
	if (game->rays[i].bott_pix > SCREEN_HEIGHT)
		game->rays[i].bott_pix = SCREEN_HEIGHT;
	if (game->rays[i].top_pix < 0)
		game->rays[i].top_pix = 0;
}

void	ray_casting_and_calculation(t_game *game)
{
	float	angle_beta;
	float	min_distance;
	int		i;

	game->inter->alpha = game->pl_inf->rot_angle - deg2rad(FOV / 2.0);
	min_distance = TILE_SIZE * 0.1;
	i = -1;
	normalize_ang(&game->inter->alpha);
	while (++i < SCREEN_WIDTH)
	{
		angle_beta = game->inter->alpha - game->pl_inf->rot_angle;
		normalize_ang(&angle_beta);
		calculate_ray_data(game, i, angle_beta, min_distance);
		game->inter->alpha += game->ray_ang;
		normalize_ang(&game->inter->alpha);
	}
}

void	render_walls_and_ceiling_floor(t_game *game)
{
	int	i;

	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		if (!draw_textured_wall(game, i))
			return ;// free return 0
		draw_ceiling_floor(i, game, game->rays[i].bott_pix,
			game->rays[i].top_pix);
	}
}

void	render_3d_game(t_game *game)
{
	ray_casting_and_calculation(game);
	render_walls_and_ceiling_floor(game);
}

void	draw_ceiling_floor(int i, t_game *game, int bott_pix, int top_pix)
{
	int	j;

	j = 0;
	while (j < top_pix)
	{
		mlx_put_pixel(game->game_img, i, j, get_rgba(game->map_inf->red_c,
				game->map_inf->green_c, game->map_inf->blue_c, 255));
		j++;
	}
	j = bott_pix;
	while (j < SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->game_img, i, j, get_rgba(game->map_inf->red_f,
				game->map_inf->green_f, game->map_inf->blue_f, 255));
		j++;
	}
}
