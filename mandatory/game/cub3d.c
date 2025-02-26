/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:54 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 13:02:14 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// void f()
// {
// 	system("leaks cub3D");
// }

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
	mlx_loop_hook(game->game, cube3d, (void *)game);
	mlx_loop(game->game);
	return (0);
}
