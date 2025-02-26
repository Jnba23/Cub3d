/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:48:25 by asayad            #+#    #+#             */
/*   Updated: 2025/02/26 13:41:13 by asayad           ###   ########.fr       */
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
	if (game->game_img)
		mlx_delete_image(game->game, game->game_img);
	if (game->mmap_image)
		mlx_delete_image(game->game, game->mmap_image);
}

size_t	ft_strlcpy_split(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (dstsize == 0)
		return (j);
	else
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
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
