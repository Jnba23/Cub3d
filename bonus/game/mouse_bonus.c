/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayad <asayad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:29:40 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/26 17:58:11 by asayad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_game			*game;
	static int		first_call;
	static double	last_x;
	double			delta_x;
	double			rotate_speed;

	(void)ypos;
	first_call = 1;
	delta_x = xpos - last_x;
	rotate_speed = 0.002;
	game = (t_game *)param;
	if (first_call)
	{
		last_x = xpos;
		first_call = 0;
		return ;
	}
	last_x = xpos;
	game->pl_inf->rot_angle += delta_x * rotate_speed;
	if (game->pl_inf->rot_angle < 0)
		game->pl_inf->rot_angle += 2 * PI;
	else if (game->pl_inf->rot_angle > 2 * PI)
		game->pl_inf->rot_angle -= 2 * PI;
	game->render = true;
}
