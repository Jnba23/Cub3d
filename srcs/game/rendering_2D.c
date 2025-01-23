/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_2D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:06 by hmoukit           #+#    #+#             */
/*   Updated: 2025/01/23 22:08:48 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cube3d(void *game)
{
	t_game 		*gm;

	gm = (t_game *)game;
	if (mlx_is_key_down(gm->game, MLX_KEY_W))
		render_move(gm, 'U');
	if (mlx_is_key_down(gm->game, MLX_KEY_S))
		render_move(gm, 'D');
	if (mlx_is_key_down(gm->game, MLX_KEY_A))
		render_move(gm, 'L');
	if (mlx_is_key_down(gm->game, MLX_KEY_D))
		render_move(gm, 'R');
	if (mlx_is_key_down(gm->game, MLX_KEY_LEFT))
		render_va(gm, 'L');
	if (mlx_is_key_down(gm->game, MLX_KEY_RIGHT))
		render_va(gm, 'R');
	if (gm->render)
	{
		render_2D_map(gm);
		cast_rays(gm);
		render_3D_game(gm);
		gm->render = false;
	}
}

void	render_2D_map(t_game *game)
{
	t_mmap	m_map;

	m_map.diameter = MMAP_DIAMETER;
	m_map.scale = SCALE;
	m_map.gm_x0 = game->pl_x_pix - (MINI_MAP_RADIUS / m_map.scale);
	m_map.gm_y0 = game->pl_y_pix - (MINI_MAP_RADIUS / m_map.scale);
	m_map.img_y = -1.0;
	while (++m_map.img_y < m_map.diameter)
	{
		m_map.img_x = -1.0;
		while(++m_map.img_x < m_map.diameter)
		{
			if (inside_mmap(m_map.img_x, m_map.img_y))
			{
				if (inside_strip(m_map.img_x, m_map.img_y))
					mlx_put_pixel(game->mmap_image, (int)m_map.img_x, (int)m_map.img_y, 0x000000AA);
				else
					mmap_2D(game, &m_map);
			}
		}
	}
	mmap_cnst(game, &m_map);
}

void	mmap_2D(t_game *game, t_mmap *m_map)
{
	m_map->gm_x = m_map->gm_x0 + m_map->img_x / m_map->scale;
	m_map->gm_y = m_map->gm_y0 + m_map->img_y / m_map->scale;
	m_map->map_x = (int)(m_map->gm_x / TILE_SIZE);
	m_map->map_y = (int)(m_map->gm_y / TILE_SIZE);
	if (m_map->map_y >= 0 && m_map->map_y < game->map_inf->map_height
		&& m_map->map_x >= 0 && m_map->map_x < ft_strlen(game->map[m_map->map_y]))
	{
		if (game->map[m_map->map_y][m_map->map_x] == '1')
			mlx_put_pixel(game->mmap_image, m_map->img_x, m_map->img_y, 0x000000FF);
		else
			mlx_put_pixel(game->mmap_image, m_map->img_x, m_map->img_y, 0xFFFFFFFF);
	}
	else
		mlx_put_pixel(game->mmap_image, m_map->img_x, m_map->img_y, 0x000000FF);
}

void	mmap_cnst(t_game *game, t_mmap *m_map)
{
	m_map->n = mlx_texture_to_image(game->game, mlx_load_png("./n_arr.png"));
	mlx_resize_image(m_map->n, 40, 40);
	mlx_image_to_window(game->game, m_map->n, MINI_MAP_RADIUS - 20, 0);
	draw_player(game);
	// render_ray(game);
}

void	draw_player(t_game *game)
{
	int x;
	int y;
	
	x = -3;
	while (++x <= 2)
	{
		y = -3;
		while (++y <= 2)
		{
			if (pow(x, 2) + pow(y, 2) <= 4)
				mlx_put_pixel(game->mmap_image, MINI_MAP_RADIUS + x, MINI_MAP_RADIUS + y, 0xFF0000FF);
		}
	}
}
