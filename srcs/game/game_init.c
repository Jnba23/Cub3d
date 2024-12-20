/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:48:52 by asayad            #+#    #+#             */
/*   Updated: 2024/12/20 19:33:48 by asayad           ###   ########.fr       */
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
	
	ray_ang = deg2rad(RAY_ANG) - M_PI;
	// game->rays->ray_lenght = RAY_L;
	va = game->player_inf->rot_angle - deg2rad(FOV / 2);
	// printf("ray angle : %f, va : %f, max_va : %f\n", ray_ang, va, game->player_inf->rot_angle + deg2rad(FOV / 2));
	// while (va < game->player_inf->rot_angle + deg2rad(FOV / 2))
	// {
		cast_ray(va, game);
		render_ray(va, game);
		//render wall
	// 	va += ray_ang;
	// }
	// reset_mvs_indic(game);
}

// void	cast_ray(float va, t_game *game)
// {
// 	float	vx;
// 	float	vy;
// 	float	hx;
// 	float	hy;
// 	//calculate first horiz intersection :
// 	game->rays->up = va_y_up(va);
// 	// printf("ray_up : %d\n", game->rays->up);
// 	//since P and A are on the same tile, we'll round up Py up or down depending on the ray's direction
// 	if (game->rays->up)
// 		vy = floor(game->player_y_pix / game->tile_height) * game->tile_height - 1;
// 	else
// 		vy = floor(game->player_y_pix / game->tile_height) * game->tile_height + game->tile_height;
// 	vx = (game->player_y_pix - vy) * tan(va);//game->player_x_pix + ;
// 	printf("vx : %f, vy : %f\n", vx, vy);
// 	// printf("vx : %f, map vx : %f\n", vx, vx / game->tile_width);
// 	if (floor(vy / game->tile_height) >= 0 && floor(vy / game->tile_height) < game->map_inf->map_height
// 		&& floor(vx / game->tile_width) >= 0 && floor(vx / game->tile_width) < ft_strlen(game->map[(int)floor(vy / game->tile_height)])
// 		&& game->map[(int)floor(vy / game->tile_height)][(int)floor(vx / game->tile_width)] != '1')
// 	{
// 		while (floor(vy / game->tile_height) >= 0 && floor(vy / game->tile_height) < game->map_inf->map_height
// 		&& floor(vx / game->tile_width) >= 0 && floor(vx / game->tile_width) < ft_strlen(game->map[(int)floor(vy / game->tile_height)])
// 		&& game->map[(int)floor(vy / game->tile_height)][(int)floor(vx / game->tile_width)] != '1')
// 		{
// 			if (game->rays->up)
// 				vy -= game->tile_height;
// 		else
// 				vy += game->tile_height;
// 			vx = (game->player_y_pix - vy) * tan(va);//game->player_x_pix + ;
// 		}
// 	}
// 	//calculate second vertical intersection :
// 	game->rays->right = va_x_right(va);
// 	if (game->rays->right)
// 		hx = floor(game->player_x_pix / game->tile_width) * game->tile_width + game->tile_width;
// 	else
// 		hx = floor(game->player_x_pix / game->tile_width) * game->tile_width - 1;
// 	hy = tan(va) * (hx - game->player_x_pix);//game->player_y_pix + ;
// 	// printf("hy : %f, hx : %f\n", hy / game->tile_height, hx / game->tile_width);
// 	if (floor(hy / game->tile_height) >= 0 && floor(hy / game->tile_height) < game->map_inf->map_height
// 		&& floor(hx / game->tile_width) >= 0 && ft_strlen(game->map[(int)floor(hy / game->tile_height)])
// 		&& game->map[(int)floor(hy / game->tile_height)][(int)floor(hx / game->tile_width)] != '1')
// 	{
// 		while (floor(hy / game->tile_height) >= 0 && floor(hy / game->tile_height) < game->map_inf->map_height
// 		&& floor(hx / game->tile_width) >= 0 &&  floor(hx / game->tile_width) < ft_strlen(game->map[(int)floor(hy / game->tile_height)])
// 		&& game->map[(int)floor(hy / game->tile_height)][(int)floor(hx / game->tile_width)] != '1')
// 		{
// 			if (game->rays->right)
// 				hx += game->tile_width;
// 			else
// 				hx -= game->tile_width;
// 			hy = tan(va) * (hx - game->player_x_pix);//game->player_y_pix + ;
// 		}
// 	}
// 	if (sqrt(square(vx - game->player_x_pix) + square(vy - game->player_y_pix)) >= sqrt(square(hx - game->player_x_pix) + square(hy - game->player_y_pix)))
// 	{
// 		game->rays->ray_lenght = sqrt(square(hx - game->player_x_pix) + square(hy - game->player_y_pix));
// 		game->rays->x = hx + MINI_MAP_RADIUS;//- game->player_x_pix;
// 		game->rays->y = hy + MINI_MAP_RADIUS;//- game->player_y_pix;
// 		printf("mmp_r : %f, horiz :hx : %f, hy : %f, x_r : %f, y_r : %f\n", MINI_MAP_RADIUS ,hx, hy, game->rays->x, game->rays->y);
// 		game->rays->horiz = true;
// 	}
// 	else
// 	{
// 		game->rays->ray_lenght = sqrt(square(vx - game->player_x_pix) + square(vy - game->player_y_pix));
// 		game->rays->x = vx + MINI_MAP_RADIUS;
// 		game->rays->y = vy + MINI_MAP_RADIUS;
// 		printf("mmp_r : %f, verti : vx : %f, vy : %f, x_r : %f, y_r : %f\n", MINI_MAP_RADIUS, vx, vy, game->rays->x, game->rays->y);
// 		game->rays->horiz = false;
// 	}
// }
void	cast_ray(float va, t_game *game)
{
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	//calculate first horizontal intersection :
	game->rays->up = va_y_up(va);
	if (game->rays->up)
		hy = floor(fmod(game->player_y_pix, game->tile_height)) * -1 - 1;
	else
		hy = floor(fmod(game->player_y_pix, game->tile_height)) + game->tile_height;
	hx = hy / tan(va);
	// printf("hx : %f, hy : %f\n", hx, hy);
	if (valid_ray_intersection(game, hx, hy))
	{
		while (valid_ray_intersection(game, hx, hy))
		{
			if (game->rays->up)
				hy -= game->tile_height;
		else
				hy += game->tile_height;
			hx = hy / tan(va);
		}
	}
	//calculate second vertical intersection :
	game->rays->right = va_x_right(va);
	if (game->rays->right)
		vx = floor(fmod(game->plane_origin_y, game->tile_width)) + game->tile_width;
	else
		vx = floor(fmod(game->player_x_pix, game->tile_width)) * -1 - 1;
	vy = tan(va) * vx;
	if (valid_ray_intersection(game, vx, vy))
	{
		while (valid_ray_intersection(game, vx, vy))
		{
			if (game->rays->right)
				vx += game->tile_width;
			else
				vx -= game->tile_width;
			vy = tan(va) * vx;
		}
	}
	if (sqrt(square(vx) + square(vy)) >= sqrt(square(hx) + square(hy)))
	{
		game->rays->ray_lenght = sqrt(square(hx) + square(hy));
		game->rays->x = hx + MINI_MAP_RADIUS;
		game->rays->y = hy + MINI_MAP_RADIUS;
		// printf("mmp_r : %f, horiz :hx : %f, hy : %f, x_r : %f, y_r : %f\n", MINI_MAP_RADIUS ,hx, hy, game->rays->x, game->rays->y);
		game->rays->horiz = true;
	}
	else
	{
		game->rays->ray_lenght = sqrt(square(vx) + square(vy));
		game->rays->x = vx;
		game->rays->y = vy;
		// printf("mmp_r : %f, verti : vx : %f, vy : %f, x_r : %f, y_r : %f\n", MINI_MAP_RADIUS, vx, vy, game->rays->x, game->rays->y);
		game->rays->horiz = false;
	}
}

bool valid_ray_intersection(t_game *game, float hx, float hy)
{
    return (floor((game->player_y_pix + hy) / game->tile_height) >= 0 &&
            floor((game->player_y_pix + hy) / game->tile_height) < game->map_inf->map_height &&
            floor((game->player_x_pix + hx) / game->tile_width) >= 0 &&
            floor((game->player_x_pix + hx) / game->tile_width) < ft_strlen(game->map[(int)floor((game->player_y_pix + hy) / game->tile_height)]) &&
            game->map[(int)floor((game->player_y_pix + hy) / game->tile_height)]
                    [(int)floor((game->player_x_pix + hx) / game->tile_width)] != '1');
}

void render_ray(float va, t_game *game)
{
	(void)va;
    t_coor	coo;
    int		d_p;
    
    coo.x0 = MINI_MAP_RADIUS + fmod(game->player_x_pix, game->tile_width);
    coo.y0 = MINI_MAP_RADIUS + fmod(game->player_y_pix, game->tile_height);
    coo.x1 = coo.x0 + (int)round(game->rays->x);
    coo.y1 = coo.y0 + (int)round(game->rays->y);
    coo.dx = abs(coo.x1 - coo.x0);
    coo.dy = abs(coo.y1 - coo.y0);
    if (coo.x0 < 0 || coo.x0 >= MAP_WIDTH || 
        coo.y0 < 0 || coo.y0 >= MAP_HEIGHT ||
        coo.x1 < - MAP_WIDTH || coo.x1 >= MAP_WIDTH || 
        coo.y1 < - MAP_HEIGHT || coo.y1 >= MAP_HEIGHT)
    {
        // printf("ERROR: Ray coordinates out of minimap bounds\n");
        return;
    }
	if (coo.x0 < coo.x1)
    	coo.sx = 1 ;
	else
		coo.sx = -1;
	if (coo.y0 < coo.y1)
    	coo.sy = 1;
	else
		coo.sy = -1;
    
    coo.dec_param = coo.dx - coo.dy;
	// printf("x1 : %d, y1 : %d\n", coo.x1, coo.y1);
    while (1)
    {
        if (square(coo.x0 - MINI_MAP_RADIUS) + square(coo.x1 - MINI_MAP_RADIUS) <= square(MINI_MAP_RADIUS))
			mlx_put_pixel(game->mmp_win, coo.x0, coo.y0, 0xFF000000 | 255);
        // printf("x0 : %d, y0 : %d\n", coo.x0, coo.y0);
        // Check if we're close enough to the end point
        if (abs(coo.x0 - coo.x1) <= 1 && abs(coo.y0 - coo.y1) <= 1)
        {
			// printf("broke at  x0 : %d, y0 : %d\n", coo.x0, coo.y0);
            break;
		}
        d_p = coo.dec_param * 2;
        if (d_p > -coo.dy)
        {
            coo.dec_param -= coo.dy;
            coo.x0 += coo.sx;
        }
        if (d_p < coo.dx)
        {
            coo.dec_param += coo.dx;
            coo.y0 += coo.sy;
        }
    }
}

int	va_x_right(float va)
{
	if ((va >= 0 && va <= M_PI / 2) || (va >= (2 * M_PI) / 2 && va <= 2 * M_PI))
		return (1);
	return (0);
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
