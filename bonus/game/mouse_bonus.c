/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:29:40 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/18 19:29:15 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	mouse_hook(double xpos, double ypos, void *param)
{
	(void)ypos;
    t_game *game = (t_game *)param;
    static int first_call = 1;
    static double last_x; 

    if (first_call)  // Initialize last_x on the first call
    {
        last_x = xpos;
        first_call = 0;
        return;
    }
    double delta_x = xpos - last_x;
    last_x = xpos; // Update last_x for the next frame
    double rotate_speed = 0.002; // Sensitivity
    game->pl_inf->rot_angle += delta_x * rotate_speed;
    if (game->pl_inf->rot_angle < 0)
        game->pl_inf->rot_angle += 2 * PI;
    else if (game->pl_inf->rot_angle > 2 * PI)
        game->pl_inf->rot_angle -= 2 * PI;

    game->render = true;
}
