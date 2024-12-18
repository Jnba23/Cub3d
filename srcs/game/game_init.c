/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:48:52 by asayad            #+#    #+#             */
/*   Updated: 2024/12/18 15:46:39 by asayad           ###   ########.fr       */
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
				mlx_put_pixel(game->mmp_win, pixel_x, pixel_y, 0xFF000000 | 255);
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
	float	va;
	double	ray_ang;
	
	ray_ang = deg2rad(RAY_ANG);
	// game->rays->ray_lenght = RAY_L;
	va = game->player_inf->rot_angle - deg2rad(FOV / 2);
	// printf("va : %f\n", va);
	while (va <= game->player_inf->rot_angle + deg2rad(FOV / 2))
	{
		cast_ray(va, game);
		render_ray(va, game);
		//render wall
		va += ray_ang;
	}
	reset_mvs_indic(game);
}

void	cast_ray(float va, t_game *game)
{
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	//calculate first horiz intersection :
	game->rays->up = va_y_up(va);
	printf("ray_up : %d\n", game->rays->up);
	//since P and A are on the same tile, we'll round up Py up or down depending on the ray's direction
	if (game->rays->up)
		vy = floor(game->player_y_pix / game->tile_height) * game->tile_height - 1;
	else
		vy = floor(game->player_y_pix / game->tile_height) * game->tile_height + game->tile_height;
	vx = game->player_x_pix + fabsf(game->player_y_pix - vy) * tan(va);
	// printf("vy : %f, map vy : %f\n", vy, vy / game->tile_height);
	// printf("vx : %f, map vx : %f\n", vx, vx / game->tile_width);
	if (floor(vy / game->tile_height) >= 0 && floor(vy / game->tile_height) < game->map_inf->map_height
		&& floor(vx / game->tile_width) >= 0 && floor(vx / game->tile_width) < ft_strlen(game->map[(int)floor(vy / game->tile_height)])
		&& game->map[(int)floor(vy / game->tile_height)][(int)floor(vx / game->tile_width)] != '1')
	{
		while (floor(vy / game->tile_height) >= 0 && floor(vy / game->tile_height) < game->map_inf->map_height
		&& floor(vx / game->tile_width) >= 0 && floor(vx / game->tile_width) < ft_strlen(game->map[(int)floor(vy / game->tile_height)])
		&& game->map[(int)floor(vy / game->tile_height)][(int)floor(vx / game->tile_width)] != '1')
		{
			if (game->rays->up)
				vy -= game->tile_height;
			else
				vy += game->tile_height;
			vx = game->player_x_pix + fabsf(game->player_y_pix - vy) * tan(va);
		}
	}
	//calculate second vertical intersection :
	game->rays->right = va_x_right(va);
	if (game->rays->right)
		hx = floor(game->player_x_pix / game->tile_width) * game->tile_width + game->tile_width;
	else
		hx = floor(game->player_x_pix / game->tile_width) * game->tile_width - 1;
	hy = game->player_y_pix + tan(va) * fabsf(hx - game->player_x_pix);
	// printf("hy : %f, hx : %f\n", hy / game->tile_height, hx / game->tile_width);
	if (floor(hy / game->tile_height) >= 0 && floor(hy / game->tile_height) < game->map_inf->map_height
		&& floor(hx / game->tile_width) >= 0 && ft_strlen(game->map[(int)floor(hy / game->tile_height)])
		&& game->map[(int)floor(hy / game->tile_height)][(int)floor(hx / game->tile_width)] != '1')
	{
		while (floor(hy / game->tile_height) >= 0 && floor(hy / game->tile_height) < game->map_inf->map_height
		&& floor(hx / game->tile_width) >= 0 &&  floor(hx / game->tile_width) < ft_strlen(game->map[(int)floor(hy / game->tile_height)])
		&& game->map[(int)floor(hy / game->tile_height)][(int)floor(hx / game->tile_width)] != '1')
		{
			if (game->rays->right)
				hx += game->tile_width;
			else
				hx -= game->tile_width;
			hy = game->player_y_pix + tan(va) * fabsf(hx - game->player_x_pix);
		}
	}
	if (sqrt(square(vx - game->player_x_pix) + square(vy - game->player_y_pix)) >= sqrt(square(hx - game->player_x_pix) + square(hy - game->player_y_pix)))
	{
		game->rays->ray_lenght = sqrt(square(hx - game->player_x_pix) + square(hy - game->player_y_pix));
		game->rays->x = hx - game->player_x_pix;
		game->rays->y = hy - game->player_y_pix;
		game->rays->horiz = true;
	}
	else
	{
		game->rays->ray_lenght = sqrt(square(vx - game->player_x_pix) + square(vy - game->player_y_pix));
		game->rays->x = (vx - game->player_x_pix);
		game->rays->y = (vy - game->player_y_pix);
		game->rays->horiz = false;
	}
}

void	render_ray(float va, t_game *game) // draw line here 
{
	(void) va;
	t_coor	coo;
	int		i;
	int		d_p; //dec_param updated

	// fprintf(stderr, "ray_l :%f, r_l : %f\n", game->rays->ray_lenght, sqrt(square(game->rays->x) + square(game->rays->y)) / game->tile_height);
	i = 0;
	coo.x0 = (int)round(game->player_x_pix);
	coo.x1 = (int)round(game->rays->x);
	coo.y0 = (int)round(game->player_y_pix);
	coo.y1 = (int)round(game->rays->y);
	coo.dx = abs(coo.x0 - coo.x1);
	coo.dy = abs(coo.y0 - coo.y1);
	if (coo.x0 < coo.x1)
		coo.sx = 1;
	else
		coo.sx = -1;
	if (coo.y0 < coo.y1)
		coo.sy = 1;
	else
		coo.sy = -1;
	coo.dec_param = coo.dx - coo.dy;
	while (1)
	{
		printf("x0 : %d, y0 : %d\n", coo.x0, coo.y0);
		printf("x1 : %d, y1 : %d\n", coo.x1, coo.y1);
		// if (coo.x0 >= 0 && coo.x0 < MAP_WIDTH && coo.y0 >= 0 && coo.y0 < MAP_HEIGHT)
			mlx_put_pixel(game->mmp_win, coo.x0 + MINI_MAP_RADIUS, coo.y0 + MINI_MAP_RADIUS, 0xFF000000 | 255);
		if (coo.x0 == coo.x1 && coo.y0 == coo.y1)
			break ;
		d_p = coo.dec_param * 2;
		if (d_p > -coo.dy)
		{
			coo.dec_param -= coo.dy;
			coo.x0 += coo.sx;
		}
		if (d_p < coo.dx)
		{
			coo.dec_param += coo.dy;
			coo.y0 += coo.sy;
		}
	}
	
	// float	a;
	// float	b;
	// int		i;
	// i = 0;
	
	// // printf("rl : %f\n", game->rays->ray_lenght);
	// while (i < game->rays->ray_lenght)
	// {	
	// 	a = MINI_MAP_RADIUS + fmod(game->player_x_pix, game->tile_width) + (cos(va) * i);
	// 	b = MINI_MAP_RADIUS + fmod(game->player_y_pix, game->tile_height) + (sin(va) * i);
	// 	// printf("a : %f, b : %f\n", a, b);
	// 	if (a >= 0 && b >= 0 && 
    //         a < game->mmp_win->width && 
    //         b < game->mmp_win->height)
    //     {
	// 		mlx_put_pixel(game->mmp_win, (int)a, (int)b, 0xFF000000 | 255);
	// 	}
	// 	i++;
	// }
}

// void    initialize_line(t_game *game)
// {
//     t_line *line;

//     line = malloc(sizeof(t_line));
//     line->x = (int)floor(game->player_x_pix);
//     line->y = (int)floor(game->player_y_pix);
//     line->dx = abs((int)floor(game->rays->x) - line->x);
//     line->dy = abs((int)floor(game->rays->y) - line->y);
//     // printf("dx : %d, dy : %d\n", line->dx, line->dy);
//     line->sx = -1;
//     if (line->x < (int)floor(game->rays->x))
//         line->sx = 1;
//     line->sy = -1;
//     if (line->y < (int)floor(game->rays->y))
//         line->sy = 1;
//     line->err = (line->dy * -1) / 2;
//     if (line->dx > line->dy)
//         line->err = line->dx / 2;
//     game->line = line;
// }

// void    render_ray(t_game *game)
// {
//     int    e2;

//     e2 = 0;
//     initialize_line(game);
//     while (1)
//     {
//         if (game->line->x < 0 || game->line->y < 0)
//             break ;
//         printf("x === [%d] || y === [%d]\n", game->line->x, game->line->y);
//         mlx_put_pixel(game->mmp_win, game->line->x, game->line->y, 0xFBFF000F);
//         // printf("x_p === [%f] || y_p === [%f]\n", game->player_x_pix, game->player_y_pix);
//         printf("rays_x === [%d] || rays_y === [%d]\n", (int)round(game->rays->x), (int)round(game->rays->y));
//         if (game->line->x == (int)round(game->rays->x) && game->line->y == (int)round(game->rays->y))
//         {
//             printf("I'M ABOUT TO BREAK\n");
//             break ;
//         }
//         e2 = game->line->err;
//         if (e2 > game->line->dx * -1)
//         {
//             game->line->err -= game->line->dy;
//             game->line->x += game->line->sx;
//         }
//         if (e2 < game->line->dy)
//         {
//             game->line->err += game->line->dx;
//             game->line->y += game->line->sy;
//         }
//     }
// }

int	va_x_right(float va)
{
	if ((va >= 0 && va <= M_PI / 2) || (va >= (2 * M_PI) / 2 && va <= 2 * M_PI))
		return (0);
	return (1);
}

int	va_y_up(float va)
{
	if ((va >= 0 && va <= M_PI))
		return (0);
	return (1);
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
