/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:48:52 by asayad            #+#    #+#             */
/*   Updated: 2024/12/08 10:12:12 by asayad           ###   ########.fr       */
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

 