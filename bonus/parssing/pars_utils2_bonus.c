/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:48:25 by asayad            #+#    #+#             */
/*   Updated: 2025/03/01 14:03:35 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	free_in_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	delete_images(t_game *game)
{
	if (game->mmap_inf->n)
		mlx_delete_image(game->game, game->mmap_inf->n);
	if (game->text->img_east)
		mlx_delete_image(game->game, game->text->img_east);
	if (game->text->img_west)
		mlx_delete_image(game->game, game->text->img_west);
	if (game->text->img_north)
		mlx_delete_image(game->game, game->text->img_north);
	if (game->text->img_south)
		mlx_delete_image(game->game, game->text->img_south);
	if (game->text->img_door)
		mlx_delete_image(game->game, game->text->img_door);
	if (game->game_img)
		mlx_delete_image(game->game, game->game_img);
	if (game->mmap_image)
		mlx_delete_image(game->game, game->mmap_image);
}

void	print_error(char *err)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err, 2);
}

int	table_size(char **map)
{
	int		i;

	i = 0;
	if (!map || !map[0])
		return (0);
	while (map[i])
		i++;
	return (i);
}

int	map_elements(t_map *map_inf)
{
	printf("NO %d\n", map_inf->no);
	printf("SO %d\n", map_inf->so);
	printf("EA %d\n", map_inf->ea);
	printf("WE %d\n", map_inf->we);
	printf("F %d\n", map_inf->floor);
	printf("C %d\n", map_inf->ceiling);
	printf("D %d\n", map_inf->d);
	if (map_inf->ea != 1 || map_inf->we != 1 || map_inf->no != 1
		|| map_inf->so != 1 || map_inf->ceiling != 1
		|| map_inf->floor != 1 || map_inf->d != 1)
		return (print_error("Missing or duplicate map data !"), 0);
	return (1);
}
