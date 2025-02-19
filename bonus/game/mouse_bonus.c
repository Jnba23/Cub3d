/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:29:40 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/19 16:48:12 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	mouse_hook(double xpos, double ypos, void *param)
{
	static int		first_call = 1;
	static double	last_x;
	t_game			*game;

	(void)ypos;
	game = (t_game *)param;
	if (first_call)
	{
		last_x = xpos;
		first_call = 0;
		return ;
	}
	last_x = xpos;
	game->pl_inf->rot_angle += (xpos - last_x) * 0.002;
	if (game->pl_inf->rot_angle < 0)
		game->pl_inf->rot_angle += 2 * PI;
	else if (game->pl_inf->rot_angle > 2 * PI)
		game->pl_inf->rot_angle -= 2 * PI;
	game->render = true;
}
