/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:48:52 by asayad            #+#    #+#             */
/*   Updated: 2024/12/12 20:20:44 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	start_game(t_map *map_inf)
{
	t_game		game;
	t_player	player_inf;
	t_ray		ray[2];

	game.rays = ray;
	game_struct_init(map_inf, &game, &player_inf, ray);
	window_init(&game, map_inf);
	//minimap
	mlx_loop_hook(game.game, move_player, (void *)&game);
	mlx_loop(game.game);
	return (0);
}

void	game_struct_init(t_map *map_inf, t_game *game, t_player *player_inf, t_ray *rays)
{
	game->map = map_inf->map_2d;
	game->map_inf = map_inf;
	game->player_inf = player_inf;
	game->rays = rays;
	game->player_inf->player_x = map_inf->p_pos_x;
	game->player_inf->player_y = map_inf->p_pos_y;
	game->player_inf->player_dir = map_inf->player_dir;
	game->player_inf->walk_dir = 0;
	game->player_inf->turn_dir = 0;
	game->player_inf->rot_angle = M_PI * 3 / 2.0;
	game->player_inf->rot_speed = deg2rad(1);
	game->scale_factor_x = (float)(MAP_WIDTH / (game->map_inf->map_width / 3));
	game->scale_factor_y = (float)(MAP_HEIGHT / (game->map_inf->map_height / 3));
	game->scale = MIN(game->scale_factor_x, game->scale_factor_y);
	game->plane_origin_x = game->player_inf->player_x * game->scale;
	game->plane_origin_y = game->player_inf->player_y * game->scale;
	game->tile_width = game->plane_origin_x / game->player_inf->player_x;
	game->tile_height = game->plane_origin_y / game->player_inf->player_y;
	game->player_x_pix = game->plane_origin_x + game->tile_width / 2;
	game->player_y_pix = game->plane_origin_y + game->tile_height / 2;
	game->last_render_x = game->player_x_pix;
	game->last_render_y = game->player_y_pix;
}

void	move_player(void *game)
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
	render_mini_map(gm);
}

void	render_move(t_game *game, char dir)
{
	char	**map;
	
	map = game->map;
	if (dir == 'U' || dir == 'D')
	{
		if (dir == 'U')
			game->player_inf->walk_dir = 1;
		else
			game->player_inf->walk_dir = -1;
		update_map_u_d(game);
	}
	if (dir == 'L' || dir == 'R')
	{
		if (dir == 'L')
			game->player_inf->turn_dir = 1;
		else
			game->player_inf->turn_dir = -1;
		update_map_l_r(game);
	}
}

void	window_init(t_game *game, t_map *map_inf)
{
	(void)map_inf;
	game->game = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba", 1);
	game->game_win = mlx_new_image(game->game, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->mmp_win = mlx_new_image(game->game, MINI_MAP_RADIUS * 2, MINI_MAP_RADIUS * 2);
	mlx_image_to_window(game->game, game->game_win, 0, 0);
	mlx_image_to_window(game->game, game->mmp_win, 0, 0);
}

void	render_mini_map(t_game* game)
{
	float	pixel_x;
	float	pixel_y;
	int		x;
	int		y;

	pixel_y = 10;
	while (pixel_y < MINI_MAP_RADIUS * 2)
	{
		pixel_x = 10;
		while (pixel_x < MINI_MAP_RADIUS * 2)
		{
			if (square(pixel_x - MINI_MAP_RADIUS) + square(pixel_y - MINI_MAP_RADIUS) <= square(MINI_MAP_RADIUS))
			{
				x = (pixel_x - MINI_MAP_RADIUS) / game->tile_width + game->player_inf->player_x;
				y = (pixel_y - MINI_MAP_RADIUS) / game->tile_height + game->player_inf->player_y;
				if (y >= 0 && y < game->map_inf->map_height && x >= 0 && x < ft_strlen(game->map[y]))
				{
 					if (game->map[y][x] == '1')
						mlx_put_pixel(game->mmp_win, pixel_x, pixel_y, 0x00000000 | 255);
					else if (game->map[y][x] == '0')
						mlx_put_pixel(game->mmp_win, pixel_x, pixel_y, 0xFFFFFFFF | 255);
				}
				else
					mlx_put_pixel(game->mmp_win, pixel_x, pixel_y, 0xFFFF00FF | 255);
			}
			pixel_x++;
		}
		pixel_y++;
	}
	render_player(game);
}

void	render_player(t_game *game)
{
	float	pixel_x = MINI_MAP_RADIUS;
	float	pixel_y = MINI_MAP_RADIUS;

	while (pixel_y <= MINI_MAP_RADIUS + game->tile_height)
	{
		pixel_x = MINI_MAP_RADIUS;
		while (pixel_x <= MINI_MAP_RADIUS + game->tile_width)
		{
			if (pixel_x == fmod(game->player_x_pix, game->tile_width) + MINI_MAP_RADIUS && pixel_y == fmod(game->player_y_pix, game->tile_height) + MINI_MAP_RADIUS)
			{
				mlx_put_pixel(game->mmp_win, pixel_x, pixel_y, 0x00000000 | 255);
			}
			else
				mlx_put_pixel(game->mmp_win, pixel_x, pixel_y, 0xFFFFFFFF | 255);
			pixel_x++;
		}
		pixel_y++;
	}
	render_rays(game);
}

void	render_rays(t_game *game)
{
	int		i;
	float	a;
	float	b;
	float	va;
	double ray_ang;
	
	ray_ang = deg2rad(RAY_ANG);
	va = game->player_inf->rot_angle - deg2rad(FOV / 2);
	while (va <= game->player_inf->rot_angle + deg2rad(FOV / 2))
	{
		i = 0;
		while (i < RAY_L)
		{
			a = MINI_MAP_RADIUS + fmod(game->player_x_pix, game->tile_width) + (cos(va) * i);
			b = MINI_MAP_RADIUS + fmod(game->player_y_pix, game->tile_height) + (sin(va) * i);
			// render_ray(a, b, va, game);
			mlx_put_pixel(game->mmp_win, a, b, 0xFBFF000F);
			i++;
		}
		va += ray_ang;
	}
	reset_mvs_indic(game);
}

// void	render_ray(float x, float y, float va, t_game *game)
// {
	
// }

void	reset_mvs_indic(t_game *game)
{
	game->player_inf->turn_dir = 0;
	game->player_inf->walk_dir = 0;
}
/*pixel shading*/
// d = sqrt(square(i - DEF_HEIGHT / 2) + square(j - DEF_WIDTH / 2));
// alpha = 1 - (fabs(d) - PLAYER_RAD);
// if (alpha > 0)
// 	mlx_put_pixel(game->game_win, x * DEF_WIDTH + j, y * DEF_HEIGHT + i, (uint32_t)255 << 24 | 255);

void	update_map_u_d(t_game *game)
{
	float	x;
	float	y;
	float	p_step;

	p_step = game->player_inf->walk_dir * PLYR_SPEED;
	x = p_step * cos(game->player_inf->rot_angle);
	y = p_step * sin(game->player_inf->rot_angle);
	if (can_move(x, y, game))
	{
		game->player_y_pix += y;
		game->player_x_pix += x;
		if (game->player_y_pix / game->tile_height != game->player_inf->player_y || game->player_x_pix / game->tile_width != game->player_inf->player_x)
		{
			game->map[game->player_inf->player_y][game->player_inf->player_x] = '0';
			game->player_inf->player_y = game->player_y_pix / game->tile_height;
			game->player_inf->player_x = game->player_x_pix / game->tile_width;
			game->map[game->player_inf->player_y][game->player_inf->player_x] = game->player_inf->player_dir;
		}
	}
}

void	update_map_l_r(t_game *game)
{
	float	x;
	float	y;
	float	p_step;

	p_step = game->player_inf->turn_dir * PLYR_SPEED;
	x = p_step * cos(game->player_inf->rot_angle - (M_PI / 2));
	y = p_step * sin(game->player_inf->rot_angle - (M_PI / 2));
	if (can_move(x, y, game))
	{
		game->player_y_pix += y;
		game->player_x_pix += x;
		if (game->player_x_pix / game->tile_width != game->player_inf->player_x || game->player_y_pix / game->tile_height != game->player_inf->player_y)
		{
			game->map[game->player_inf->player_y][game->player_inf->player_x] = '0';
			game->player_inf->player_x = game->player_x_pix / game->tile_width;
			game->player_inf->player_y = game->player_y_pix / game->tile_height;
			game->map[game->player_inf->player_y][game->player_inf->player_x] = game->player_inf->player_dir;
		}
	}
}

int	can_move(float x, float y, t_game *game)
{
	float 	a[3][2];
	int 	j;
	int		x_coo;
	int		y_coo;

	j = 0;
	a[0][0] = y + game->player_y_pix;
	a[0][1] = x + game->player_x_pix;
	a[1][0] = y + game->player_y_pix + 0.3f;
	a[1][1] = x + game->player_x_pix + 0.3f;
	a[2][0] = y + game->player_y_pix - 0.3f;
	a[2][1] = x + game->player_x_pix - 0.3f;
	while (j < 3)
	{
		y_coo = (int)floor(a[j][0] / game->tile_height);
		x_coo = (int)floor(a[j][1] / game->tile_width);
		if (y_coo < 0 || y_coo > game->map_inf->map_height || x_coo < 0 || x_coo > ft_strlen(game->map[y_coo]))
			return (0);
		if (game->map[y_coo][x_coo] == '1')
			return (0) ;
		j++;
	}
	return (1);
}

void	render_va(t_game *game, char dir)
{
	if(dir == 'L')
	{
		game->player_inf->turn_dir = -1; // opposite since the plane is reversed on the screen
		game->player_inf->rot_angle += game->player_inf->turn_dir * game->player_inf->rot_speed;
	}
	else if (dir == 'R')
	{
		game->player_inf->turn_dir = +1; // opposite since the plane is reversed on the screen
		game->player_inf->rot_angle += game->player_inf->turn_dir * game->player_inf->rot_speed;
	}
	if (game->player_inf->rot_angle < 0)
		game->player_inf->rot_angle += 2 * M_PI;
}
