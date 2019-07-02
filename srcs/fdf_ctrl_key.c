/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ctrl_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 16:28:14 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/27 16:28:16 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

void	ft_fdfctrlkey_zoom(int plus, int key, t_prop *prop)
{
	if (key == KEY_Z || key == KEY_F)
	{
		if ((prop->pt_scale - 1 > 0 && !plus) || \
			(prop->pt_scale < I_MAX - 1 && plus))
			prop->pt_scale += (plus ? 1 : -1);
	}
	if (key == KEY_HH)
	{
		if (prop->ht_ratio - 0.05 > 0 || plus)
			prop->ht_ratio *= (plus ? 1.1 : 0.9);
	}
	else if (key == KEY_F)
		prop->ht_ratio = prop->ht_scale / prop->pt_scale;
	if (key == KEY_Z || key == KEY_HH)
		prop->ht_scale = prop->pt_scale * prop->ht_ratio;
	if (key == KEY_T)
		prop->clr_prop[0] = ft_fdfproj_color_set(prop->clr_prop[0], plus);
	else if (key == KEY_B)
		prop->clr_prop[1] = ft_fdfproj_color_set(prop->clr_prop[1], plus);
}

void	ft_fdfctrlkey_move(int key_arrow, int key, t_prop *prop)
{
	if (key == KEY_M)
	{
		if (key_arrow == KEY_UP || key_arrow == KEY_DOWN)
			prop->map_pos[AXIS_Y] += (key_arrow == KEY_UP ? 10 : -10);
		else
			prop->map_pos[AXIS_X] += (key_arrow == KEY_LEFT ? 10 : -10);
	}
	else
	{
		if (key_arrow == KEY_UP || key_arrow == KEY_DOWN)
			prop->angle_yaw += (key_arrow == KEY_UP ? 2 : -2) * (PI / 180);
		else
			prop->angle_pitch += (key_arrow == KEY_LEFT ? 2 : -2) * (PI / 180);
	}
}
