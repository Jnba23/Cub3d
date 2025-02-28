/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:54 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/28 12:17:40 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	f(void)
{
	system("leaks cub3D");
	system("lsof cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_map	map_inf;

	atexit(f);
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
	mlx_loop_hook(game->game, cube3d, (void *)game);
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
		cast_rays(gm);
		if (!render_3d_game(gm))
			quit_game(gm);
		gm->render = false;
	}
}
