/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:29:40 by hmoukit           #+#    #+#             */
/*   Updated: 2025/02/18 12:03:06 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// void mouse_hook(double xpos, double ypos, void *param)
// {
//     t_game *game = (t_game *)param;
//     static double last_x = SCREEN_WIDTH / 2;

//     double delta_x = xpos - last_x;
//     last_x = xpos;

//     double rotate_speed = 0.02; // Adjust sensitivity
//     if (delta_x > 0)
//         game->pl_inf->rot_angle += rotate_speed * delta_x;
//     else if (delta_x < 0)
//         game->pl_inf->rot_angle -= rotate_speed * -delta_x;

//     normalize_ang(&game->pl_inf->rot_angle); // Keep it in [0, 2*PI]
// }
