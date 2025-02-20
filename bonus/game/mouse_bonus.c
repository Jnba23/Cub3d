/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:29:40 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/20 14:49:35 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

// void	mouse_hook(double xpos, double ypos, void *param)
// {
// 	static int		first_call = 1;
// 	static double	last_x;
// 	t_game			*game;

// 	(void)ypos;
// 	game = (t_game *)param;
// 	if (first_call)
// 	{
// 		last_x = xpos;
// 		first_call = 0;
// 		return ;
// 	}
// 	last_x = xpos;
// 	game->pl_inf->rot_angle += (xpos - last_x) * 0.002;
// 	if (game->pl_inf->rot_angle < 0)
// 		game->pl_inf->rot_angle += 2 * PI;
// 	else if (game->pl_inf->rot_angle > 2 * PI)
// 		game->pl_inf->rot_angle -= 2 * PI;
// 	game->render = true;
// }


void mouse_hook(double xpos, double ypos, void *param)
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





    // Normalize angle to stay within [0, 2*PI]


    if (game->pl_inf->rot_angle < 0)


        game->pl_inf->rot_angle += 2 * PI;


    else if (game->pl_inf->rot_angle > 2 * PI)


        game->pl_inf->rot_angle -= 2 * PI;





    game->render = true;


}