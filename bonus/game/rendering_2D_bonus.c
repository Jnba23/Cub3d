/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_2D_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:06 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 19:16:19 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	render_2d_map(t_game *game)
{
	t_mmap	m_map;

	m_map.diameter = MMAP_DIAMETER;
	m_map.scale = SCALE;
	m_map.gm_x0 = game->pl_x_pix - (MINI_MAP_RADIUS / m_map.scale);
	m_map.gm_y0 = game->pl_y_pix - (MINI_MAP_RADIUS / m_map.scale);
	m_map.img_y = -1.0;
	game->mmap_inf = &m_map;
	while (++m_map.img_y < m_map.diameter)
	{
		m_map.img_x = -1.0;
		while (++m_map.img_x < m_map.diameter)
		{
			if (inside_mmap(m_map.img_x, m_map.img_y))
			{
				if (inside_strip(m_map.img_x, m_map.img_y))
					mlx_put_pixel(game->mmap_image,
						(int)m_map.img_x, (int)m_map.img_y, 0x000000AA);
				else
					mmap_2d(game, &m_map);
			}
		}
	}
	mmap_cnst(game, &m_map);
}

void	mmap_2d(t_game *game, t_mmap *m_map)
{
	m_map->gm_x = m_map->gm_x0 + m_map->img_x / m_map->scale;
	m_map->gm_y = m_map->gm_y0 + m_map->img_y / m_map->scale;
	m_map->map_x = (int)(m_map->gm_x / TILE_SIZE);
	m_map->map_y = (int)(m_map->gm_y / TILE_SIZE);
	if (m_map->map_y >= 0 && m_map->map_y < game->map_inf->map_height
		&& m_map->map_x >= 0
		&& m_map->map_x < ft_strlen(game->map[m_map->map_y]))
	{
		if (game->map[m_map->map_y][m_map->map_x] == '1')
			mlx_put_pixel(game->mmap_image, m_map->img_x,
				m_map->img_y, 0x000000FF);
		else
			mlx_put_pixel(game->mmap_image, m_map->img_x,
				m_map->img_y, 0xFFFFFFFF);
	}
	else
		mlx_put_pixel(game->mmap_image, m_map->img_x,
			m_map->img_y, 0x000000FF);
}

void	mmap_cnst(t_game *game, t_mmap *m_map)
{
	mlx_texture_t	*n;

	n = mlx_load_png("./textures/n_arr.png");
	if (!n)
	{
		free_textures(game->map_inf);
		free_table(game->map_inf->map_2d, game->map_inf->map_size);
		delete_images(game);
		exit(1);
	}
	m_map->n = mlx_texture_to_image(game->game, n);
	mlx_delete_texture(n);
	mlx_resize_image(m_map->n, 40, 40);
	if (mlx_image_to_window(game->game, m_map->n,
			MINI_MAP_RADIUS - 20, 0) == -1)
	{
		free_table(game->map_inf->map_2d, game->map_inf->map_size);
		free_textures(game->map_inf);
		delete_images(game);
		mlx_delete_image(game->game, m_map->n);
		exit(1);
	}
	draw_player(game);
}

void	draw_player(t_game *game)
{
	float	start_ang;
	float	end_ang;
	t_coor	coo;

	start_ang = game->pl_inf->rot_angle - deg2rad(FOV / 2);
	end_ang = game->pl_inf->rot_angle + deg2rad(FOV / 2);
	coo.x1 = -3;
	while (start_ang <= end_ang)
	{
		coo.x1 = (int)(cos(start_ang) * 15) + MINI_MAP_RADIUS;
		coo.y1 = (int)(sin(start_ang) * 15) + MINI_MAP_RADIUS;
		render_ray(game, &coo);
		start_ang += deg2rad(RAY_ANG);
	}
}
