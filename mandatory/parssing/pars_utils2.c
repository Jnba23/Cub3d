/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:48:25 by asayad            #+#    #+#             */
/*   Updated: 2025/03/01 12:52:26 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	if (game->text->img_east)
		mlx_delete_image(game->game, game->text->img_east);
	if (game->text->img_west)
		mlx_delete_image(game->game, game->text->img_west);
	if (game->text->img_north)
		mlx_delete_image(game->game, game->text->img_north);
	if (game->text->img_south)
		mlx_delete_image(game->game, game->text->img_south);
	if (game->game_img)
		mlx_delete_image(game->game, game->game_img);
}

int	table_size(char **map)
{
	int	i;

	i = 0;
	if (!map || !map[0])
		return (0);
	while (map[i])
		i++;
	return (i);
}

void	print_error(char *err)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err, 2);
}
