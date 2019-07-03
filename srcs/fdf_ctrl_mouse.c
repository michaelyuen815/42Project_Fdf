/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ctrl_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:50:31 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/27 14:50:33 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

/*
** function of move action by mouse control
** apply the change of x, y coordination to position of map in t_prop
** and also update the x, y coordination of mouse in t_prop
*/

void	ft_fdfctrlmouse_move(int x, int y, t_prop *prop)
{
	if (x > WINDOW_WIDTH_DEFAULT || y > WINDOW_LEN_DEFAULT)
		return ;
	prop->map_pos[AXIS_X] += x - prop->mouse_pos[AXIS_X];
	prop->map_pos[AXIS_Y] += y - prop->mouse_pos[AXIS_Y];
	prop->mouse_pos[0] = x;
	prop->mouse_pos[1] = y;
}

/*
** function of rotate action of mouse control
** apply the change of x, y coordination to angle of map in t_prop
** and also updtae the x, y coorination of mouse in t_prop
*/

void	ft_fdfctrelmouse_rotate(int x, int y, t_prop *prop)
{
	if (x > WINDOW_WIDTH_DEFAULT || y > WINDOW_LEN_DEFAULT)
		return ;
	prop->angle_pitch += (double)(x - prop->mouse_pos[AXIS_X]) * (PI / 180);
	prop->angle_yaw += (double)(y - prop->mouse_pos[AXIS_Y]) * (PI / 180);
	prop->mouse_pos[AXIS_X] = x;
	prop->mouse_pos[AXIS_Y] = y;
}
