/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:48:52 by asayad            #+#    #+#             */
/*   Updated: 2024/12/12 12:06:11 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	start_game(t_map *map_inf)
{
	t_game	game;

	game_struct_init(map_inf, &game);
	window_init(&game, map_inf);
	mlx_loop_hook(game.game, render_map, (void *)&game);
	mlx_key_hook(game.game, move_player, (void *)&game);
	mlx_loop(game.game);
	return (0);
}

void	game_struct_init(t_map *map_inf, t_game *game)
{
	game->map = map_inf->map_2d;
	game->map_heigth = map_inf->map_height;	
	game->map_width = map_inf->map_width;
	game->player_x = map_inf->p_pos_x;
	game->player_y = map_inf->p_pos_y;
	game->player_dir = map_inf->player_dir;
	game->walk_dir = 0;
	game->turn_dir = 0;
	game->rot_angle = M_PI / 2;
	game->rot_speed = deg2rad(2);
}

void	window_init(t_game *game, t_map *map_inf)
{
	if (game->map_width * DEF_WIDTH <= 2625
		&& game->map_heigth * DEF_HEIGHT <= 1425)
	{
		game->game = mlx_init(game->map_width * DEF_WIDTH,
			game->map_heigth * DEF_HEIGHT, "lo3ba", 1);
		game->game_win = mlx_new_image(game->game, game->map_width * DEF_WIDTH,
			game->map_heigth * DEF_HEIGHT);
		mlx_image_to_window(game->game, game->game_win, 0, 0);
	}
	else
	{
		free_ressources(map_inf);
		write(2, "window's too big !", 19);
	}
}

void	render_map(void* game)
{
	int		i;
	int		j;
	t_game	*game_inf;

	i = 0;
	game_inf = (t_game *)game;
	while (game_inf->map[i])
	{
		j = 0;
		while (game_inf->map[i][j])
		{
			if (game_inf->map[i][j] == '1')
				render_tile(game_inf, j, i, 0xFFFFFFFF | 255);
			if (game_inf->map[i][j] == '0')
				render_tile(game_inf, j, i,0x00000000 | 255);
			if (game_inf->map[i][j] == 'N' || game_inf->map[i][j] == 'S'
				|| game_inf->map[i][j] == 'E' || game_inf->map[i][j] == 'W')
				render_player(game_inf, 0x00000000 | 255);
			j++;
		}
		i++;
	}
}

void	render_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	tmp_clr;

	i = 0;
	j = 0;
	tmp_clr = color;
	while (i <= DEF_HEIGHT)
	{
		j = 0;
		while (j <= DEF_WIDTH)
		{
			if ((i == 0 || i == DEF_HEIGHT) || (j == 0 || j == DEF_WIDTH))
				color = 0x00ff0fff;
			mlx_put_pixel(game->game_win, x * DEF_WIDTH + j, y * DEF_HEIGHT + i, color);
			color = tmp_clr;
			j++;
		}
		i++;
	}
}

void	render_player(t_game *game, int color)
{
	int		i;
	int		j;
	int		tmp_clr;

	i = 0;
	tmp_clr = color;
	while (i <= DEF_HEIGHT)
	{
		j = 0;
		while (j <= DEF_WIDTH)
		{
			if (square(i - DEF_HEIGHT / 2) + square(j - DEF_WIDTH / 2) <= square(PLAYER_RAD))
			{
				mlx_put_pixel(game->game_win, game->player_x * DEF_WIDTH + j, game->player_y * DEF_HEIGHT + i, (uint32_t)255 << 24 | 255);
				render_ray(game);
			}
			else
			{
				if ((i == 0 || i == DEF_HEIGHT) || (j == 0 || j == DEF_WIDTH))
					color = 0x00ff0fff;
				mlx_put_pixel(game->game_win, game->player_y * DEF_WIDTH + j, game->player_y * DEF_HEIGHT + i, color);
				color = tmp_clr;
			}
			j++;
		}
		i++;
	}
	reset_mvs_indic(game);
}

void	render_ray(t_game *game)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	while (i < RAY_L)
	{
		x = game->player_x + i + cos(game->rot_angle - FOV / 2) * RAY_L;
		y = game->player_x + i + sin(game->rot_angle - FOV / 2) * RAY_L;
		mlx_put_pixel(game->game_win, x, y, (uint32_t)255 << 24 | 255);
		i++;
	}
}

void	reset_mvs_indic(t_game *game)
{
	game->turn_dir = 0;
	game->walk_dir = 0;
}
/*pixel shading*/
// d = sqrt(square(i - DEF_HEIGHT / 2) + square(j - DEF_WIDTH / 2));
// alpha = 1 - (fabs(d) - PLAYER_RAD);
// if (alpha > 0)
// 	mlx_put_pixel(game->game_win, x * DEF_WIDTH + j, y * DEF_HEIGHT + i, (uint32_t)255 << 24 | 255);

void	move_player(mlx_key_data_t key_data, void *game)
{
	t_game *gm;
	
	gm = (t_game *)game;
	if (key_data.key == MLX_KEY_W && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		render_move(gm, 'U');
	if (key_data.key == MLX_KEY_S && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		render_move(gm, 'D');
	if (key_data.key == MLX_KEY_A && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		render_move(gm, 'L');
	if (key_data.key == MLX_KEY_D && (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
		render_move(gm, 'R');
	// if (key_data.key == MLX_KEY_LEFT)
	// 	render_va(gm, 'L');
	// if (key_data.key == MLX_KEY_RIGHT)
	// 	render_va(gm, 'R');
}

void	render_move(t_game *game, char dir)
{
	char	**map;

	map = game->map;
	
	if (dir == 'U' || dir == 'D')
		update_map_u_d(game, dir);
	if (dir == 'L' || dir == 'R')
		update_map_l_r(game, dir);
	render_map((void *)game);
}

void	update_map_u_d(t_game *game, char dir)
{
	char **map;

	map = game->map;
	if (dir == 'U' && map[game->player_y - 1][game->player_x] != '1')
	{
		game->player_y -= 1;
		game->player_dir = -1; // opposite since the plane is reversed on the screen
		game->map[game->player_y][game->player_x] = game->player_dir;
		game->map[game->player_y + 1][game->player_x] = '0';
	}
	if (dir == 'D' && map[game->player_y + 1][game->player_x] != '1')
	{
		game->player_y += 1;
		game->player_dir = 1; // opposite since the plane is reversed on the screen
		game->map[game->player_y][game->player_x] = game->player_dir;
		game->map[game->player_y - 1][game->player_x] = '0';
	}
}

void	update_map_l_r(t_game *game, char dir)
{
	char **map;

	map = game->map;
	if (dir == 'L' && map[game->player_y][game->player_x - 1] != '1')
	{
		game->player_x -= 1;
		game->turn_dir = -1; // opposite since the plane is reversed on the screen
		game->map[game->player_y][game->player_x] = game->player_dir;
		game->map[game->player_y][game->player_x + 1] = '0';
	}
	if (dir == 'R' && map[game->player_y][game->player_x + 1] != '1')
	{
		game->player_x += 1;
		game->turn_dir = 1; // opposite since the plane is reversed on the screen
		game->map[game->player_y][game->player_x] = game->player_dir;
		game->map[game->player_y][game->player_x - 1] = '0';
	}
}
// void	render_va(t_game *game, char dir)
// {
// 	char	**map;

// 	map = game->map;
// }