/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:54 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 16:57:16 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>
//  void f()
//  {
// 	system("leaks cub3d_bonus");
// 	// system("lsof cub3d_bonus");
//  }
int	main(int ac, char **av)
{
	t_map	map_inf;

	// atexit(f);
	if (ac == 2)
	{
		if (ft_strlen(av[1]) >= 4 && !ft_strcmp(av[1]
				+ (ft_strlen(av[1]) - 4), ".cub") && ft_strlen(av[1]) > 4)
		{
			initialize_map(&map_inf);
			if (!check_infile(av[1], &map_inf))
				return (0);
			start_game(&map_inf);
		}
		else
			print_error("Incompatible map !!");
	}
	else
		print_error("too many or few args !");
	return (1);
}

int	start_game(t_map *map_inf)
{
	t_game		*game;
	t_player	player_inf;

	game_struct_init(map_inf, &game, &player_inf);
	window_init(game, map_inf);
	mlx_cursor_hook(game->game, mouse_hook, game);
	mlx_set_cursor_mode(game->game, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(game->game, cube3d, (void *)game);
	mlx_loop_hook(game->game, animate_torch, (void *)game);
	init_textures(game);
	mlx_loop(game->game);
	return (0);
}

void	cube3d(void *game)
{
	t_game	*gm;

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
	if (mlx_is_key_down(gm->game, MLX_KEY_ESCAPE))
		quit_game(gm);
	if (gm->render)
	{
		render_2d_map(gm);
		cast_rays(gm);
		render_3d_game(gm);
		gm->render = false;
	}
}
