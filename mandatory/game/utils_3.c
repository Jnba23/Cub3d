/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:54:23 by asayad            #+#    #+#             */
/*   Updated: 2025/03/04 01:53:13 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	release_ressources(t_game *game, t_map *map_inf)
{
	free_table(map_inf->map_2d, map_inf->map_size);
	free_textures(map_inf);
	delete_images(game);
}

void	quit_game(t_game *game)
{
	release_ressources(game, game->map_inf);
	free(game->inter);
	game->inter = NULL;
	free(game->rays);
	game->rays = NULL;
	free(game->text);
	game->text = NULL;
	mlx_terminate(game->game);
	free(game);
	game = NULL;
	exit(1);
}

void	assign_color(uint32_t *color, t_game *game)
{
	*color = (uint32_t)(game->text->pixel[0] << 24)
		| (uint32_t)(game->text->pixel[1] << 16)
		| (uint32_t)(game->text->pixel[2] << 8)
		| (uint32_t)game->text->pixel[3];
}

void	rot_ang(t_game *game)
{
	if (game->pl_inf->pl_dir == 'N')
		game->pl_inf->rot_angle = PI / 2;
	else if (game->pl_inf->pl_dir == 'S')
		game->pl_inf->rot_angle = 3 * PI / 2;
	else if (game->pl_inf->pl_dir == 'E')
		game->pl_inf->rot_angle = 0;
	else
		game->pl_inf->rot_angle = PI;
}
