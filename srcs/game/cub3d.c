/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:54 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/24 20:42:47 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int ac, char **av)
{
	t_map	map_inf;

	if (ac == 2)
	{
		if (ft_strlen(av[1]) >= 4 && !ft_strcmp(av[1]
				+ (ft_strlen(av[1]) - 4), ".cub"))
		{
			initialize_map(&map_inf);
			if (!check_infile(av[1], &map_inf))
				return (0);
			start_game(&map_inf);
		}
		else
			ft_putendl_fd("Incompatible map !!", 2);
	}
	else
		ft_putendl_fd("too many or few args !", 2);
	return (1);
}

int	start_game(t_map *map_inf)
{
	t_game		*game;
	t_player	player_inf;
	t_ray		ray;

	game_struct_init(map_inf, &game, &player_inf);
	game->rays = &ray;
	window_init(game, map_inf);
	mlx_loop_hook(game->game, move_player, (void *)game);
	mlx_loop(game->game);
	return (0);
}
