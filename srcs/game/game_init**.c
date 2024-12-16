/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init**.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:48:52 by asayad            #+#    #+#             */
/*   Updated: 2024/12/16 17:26:56 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	start_game(t_map *map_inf)
{
	t_game	game;

	game.player_inf = malloc(sizeof(t_player));
	if (!game.player_inf)
		return (0);
	game_struct_init(map_inf, &game);
	window_init(&game, map_inf);
	//minimap
	mlx_loop_hook(game.game, move_player, (void *)&game);
	mlx_loop(game.game);
	return (0);
}

void	game_struct_init(t_map *map_inf, t_game *game)
{
	game->map = map_inf->map_2d;
	game->map_inf = map_inf;
	game->player_inf->player_x = map_inf->p_pos_x;
	game->player_inf->player_x_pix = map_inf->p_pos_x * DEF_WIDTH  + DEF_WIDTH / 2;
	game->player_inf->player_y = map_inf->p_pos_y;
	game->player_inf->player_y_pix = map_inf->p_pos_y * DEF_HEIGHT + DEF_HEIGHT / 2;
	game->player_inf->player_dir = map_inf->player_dir;
	game->player_inf->walk_dir = 0;
	game->player_inf->turn_dir = 0;
	game->player_inf->rot_angle = M_PI * 3 / 2.0;
	game->player_inf->rot_speed = deg2rad(1);
}

void	window_init(t_game *game, t_map *map_inf)
{
	(void)map_inf;
	game->game = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba", 1);
	game->game_win = mlx_new_image(game->game, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(game->game, game->game_win, 0, 0);
}

void	render_mini_map(void* game)
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
			else
				render_tile(game_inf, j, i,0x00000000 | 255);
			j++;
		}
		i++;
	}
	render_player(game_inf, 0xFF000000 | 255);
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

void	render_player(t_game *game, uint32_t color)
{
	int		i;
	int		j;
	int		tmp_clr;

	i = 0;
	tmp_clr = color;
	while (i <= (DEF_HEIGHT))
	{
		j = 0;
		while (j <= DEF_WIDTH)
		{
			if (i == (int)(game->player_inf->player_y_pix) % DEF_HEIGHT && j == (int)(game->player_inf->player_x_pix) % DEF_WIDTH)
			{
				mlx_put_pixel(game->game_win, game->player_inf->player_x_pix, game->player_inf->player_y_pix, (uint32_t)255 << 24 | 255);
				render_rays(game, j, i, (uint32_t)255 << 24 | 255);
			}
			j++;
		}
		i++;
	}
	reset_mvs_indic(game);
}

void	render_rays(t_game *game, int x, int y, uint32_t color)
{
	int		i;
	float	a;
	float	b;
	float	va;

	(void)x;
	(void)y;
	va = game->player_inf->rot_angle - deg2rad(FOV / 2);
	while (va <= game->player_inf->rot_angle + deg2rad(FOV / 2))
	{
		i = 0;
		while (i < RAY_L)
		{
			a = game->player_inf->player_x_pix + cos(va) * i;
			b = game->player_inf->player_y_pix + sin(va) * i;
			mlx_put_pixel(game->game_win, a, b, color);
			i++;
		}
		va += deg2rad(3);
	}
}

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

void	move_player(void *game)
{
	t_game *gm;
	
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
		update_map_u_d(game, dir);
	}
	if (dir == 'L' || dir == 'R')
	{
		if (dir == 'L')
			game->player_inf->turn_dir = 1;
		else
			game->player_inf->turn_dir = -1;
		update_map_l_r(game, dir);
	}
	render_mini_map((void *)game);
}

void	update_map_u_d(t_game *game, char dir)
{
	float	x;
	float	y;
	float	p_step;

	(void)dir;
	p_step = game->player_inf->walk_dir * PLYR_SPEED;
	x = p_step * cos(game->player_inf->rot_angle);
	y = p_step * sin(game->player_inf->rot_angle);
	// printf("xp : %f, yp : %f\n", game->player_inf->player_x_pix , game->player_inf->player_y_pix);
	// printf("x : %f, y : %f\n", x , y);
	// printf("map char : %c\n", game->map[(int)(game->player_inf->player_y_pix + y) / DEF_HEIGHT][(int)(game->player_inf->player_x_pix + x) / DEF_WIDTH]);
	if (game->map[(int)floor((game->player_inf->player_y_pix + y) / DEF_HEIGHT)][(int)floor((game->player_inf->player_x_pix + x) / DEF_WIDTH)] != '1')
	{
		game->player_inf->player_y_pix += y;
		game->player_inf->player_x_pix += x;
		if (game->player_inf->player_y_pix / DEF_HEIGHT != game->player_inf->player_y || game->player_inf->player_x_pix / DEF_WIDTH != game->player_inf->player_x)
		{
			game->map[game->player_inf->player_y][game->player_inf->player_x] = '0';
			game->player_inf->player_y = game->player_inf->player_y_pix / DEF_HEIGHT;
			game->player_inf->player_x = game->player_inf->player_x_pix / DEF_WIDTH;
			// printf("x : %d, y : %d\n", game->player_inf->player_x, game->player_inf->player_y);
			game->map[game->player_inf->player_y][game->player_inf->player_x] = game->player_inf->player_dir;
		}
	}
	
}
// void	update_map_u_d(t_game *game, char dir)
// {
// 	char	**map;
// 	float	x;
// 	float	y;

// 	x = 
// 	map = game->map;
// 	if (dir == 'U' && map[(game->player_inf->player_y_pix - 4) / DEF_HEIGHT][game->player_inf->player_x] != '1')
// 	{
// 		game->player_inf->player_y_pix -= 4;
// 		if (game->player_inf->player_y_pix / DEF_HEIGHT != game->player_inf->player_y)
// 		{
// 			game->player_inf->player_y -= 1;
// 			game->map[game->player_inf->player_y][game->player_inf->player_x] = game->player_inf->player_dir;
// 			game->map[game->player_inf->player_y + 1][game->player_inf->player_x] = '0';
// 		}
// 		game->player_inf->turn_dir = -1; // opposite since the plane is reversed on the screen
// 	}
// 	if (dir == 'D' && map[(game->player_inf->player_y_pix + 4) / DEF_HEIGHT][game->player_inf->player_x] != '1')
// 	{
// 		game->player_inf->player_y_pix += 4;
// 		if (game->player_inf->player_y_pix / DEF_HEIGHT != game->player_inf->player_y)
// 		{
// 			game->player_inf->player_y += 1;
// 			game->map[game->player_inf->player_y][game->player_inf->player_x] = game->player_inf->player_dir;
// 			game->map[game->player_inf->player_y - 1][game->player_inf->player_x] = '0';
// 		}
// 		game->player_inf->turn_dir = 1; // opposite since the plane is reversed on the screen
// 	}
// }

void	update_map_l_r(t_game *game, char dir)
{
	float	x;
	float	y;
	float	p_step;

	(void)dir;	
	p_step = game->player_inf->turn_dir * PLYR_SPEED;
	x = p_step * cos(game->player_inf->rot_angle - (M_PI / 2));
	y = p_step * sin(game->player_inf->rot_angle - (M_PI / 2));
	// printf("xp : %f, yp : %f\n", game->player_inf->player_x_pix , game->player_inf->player_y_pix);
	// printf("xl : %f, yl : %f\n", x , y);
	// printf("old y : %d, old x : %d\n", game->player_inf->player_y, game->player_inf->player_x);
	// printf("y : %f, x : %f\n", (game->player_inf->player_y_pix + y) / DEF_HEIGHT, (game->player_inf->player_x_pix + x) / DEF_WIDTH);
	// printf("map char : %c\n", game->map[(int)(game->player_inf->player_y_pix + y) / DEF_HEIGHT][(int)(game->player_inf->player_x_pix + x) / DEF_WIDTH]);
	if (game->map[(int)floor((game->player_inf->player_y_pix + y) / DEF_HEIGHT)][(int)floor((game->player_inf->player_x_pix + x) / DEF_WIDTH)] != '1')
	{
		game->player_inf->player_y_pix += y;
		game->player_inf->player_x_pix += x;
		if (game->player_inf->player_x_pix / DEF_WIDTH != game->player_inf->player_x || game->player_inf->player_y_pix / DEF_HEIGHT != game->player_inf->player_y)
		{
			game->map[game->player_inf->player_y][game->player_inf->player_x] = '0';
			game->player_inf->player_x = game->player_inf->player_x_pix / DEF_WIDTH;
			game->player_inf->player_y = game->player_inf->player_y_pix / DEF_HEIGHT;
			// printf("xl : %d, yl : %d\n", game->player_inf->player_x, game->player_inf->player_y);
			game->map[game->player_inf->player_y][game->player_inf->player_x] = game->player_inf->player_dir;
		}
	}
}
// void	update_map_l_r(t_game *game, char dir)
// {
// 	char **map;
// 	map = game->map;
// 	if (dir == 'L' && map[game->player_inf->player_y][(game->player_inf->player_x_pix - 4) / DEF_WIDTH] != '1')
// 	{
// 		game->player_inf->player_x_pix -= 4;
// 		if (game->player_inf->player_x_pix / DEF_WIDTH != game->player_inf->player_x)
// 		{
// 			game->player_inf->player_x = (game->player_inf->player_x_pix - 1) / DEF_WIDTH;
// 			game->map[game->player_inf->player_y][game->player_inf->player_x] = game->player_inf->player_dir;
// 			game->map[game->player_inf->player_y][game->player_inf->player_x + 1] = '0';
// 		}
// 	}
// 	if (dir == 'R' && map[game->player_inf->player_y][(game->player_inf->player_x_pix + 4) / DEF_WIDTH] != '1')
// 	{
// 		game->player_inf->player_x_pix += 4;
// 		if (game->player_inf->player_x_pix / DEF_WIDTH != game->player_inf->player_x)
// 		{
// 			game->player_inf->player_x = (game->player_inf->player_x_pix + 1) / DEF_WIDTH;
// 			game->map[game->player_inf->player_y][game->player_inf->player_x] = game->player_inf->player_dir;
// 			game->map[game->player_inf->player_y][game->player_inf->player_x - 1] = '0';
// 		}
// 	}
// }
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
	// game->player_inf->rot_angle = game->player_inf->rot_angle % (2 * M_PI);
	if (game->player_inf->rot_angle < 0)
		game->player_inf->rot_angle += 2 * M_PI;
	// printf("angle : %f\n", game->player_inf->rot_angle);
}