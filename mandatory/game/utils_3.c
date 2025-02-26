/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:54:23 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 18:03:58 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	release_ressources(t_game *game, t_map *map_inf, int i)
{
	free_table(map_inf->map_2d, map_inf->map_size);
	free_textures(map_inf);
	delete_images(game);
	if (i == 1)
		exit(1);
}

void	quit_game(t_game *game)
{
	free_table(game->map_inf->map_2d, game->map_inf->map_size);
	free_textures(game->map_inf);
	// if (game->mmap_inf->n)
	// 	mlx_delete_image(game->game, game->mmap_inf->n);
	if (game->text->img_east)
		mlx_delete_image(game->game, game->text->img_east);
	if (game->text->img_west)
		mlx_delete_image(game->game, game->text->img_west);
	if (game->text->img_north)
		mlx_delete_image(game->game, game->text->img_north);
	if (game->text->img_south)
		mlx_delete_image(game->game, game->text->img_south);
	delete_images(game);
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
