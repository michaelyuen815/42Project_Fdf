/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_prop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 22:03:45 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/24 22:03:46 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

void	ft_fdfprop_init2(t_prop *prop)
{
	prop->ht_ratio = GRAPHIC_RATIO_ALTITUDE_DEFAULT;
	prop->angle_yaw = ANGLE_YAW_DEFAULT * (PI / 180);
	prop->angle_pitch = ANGLE_PITCH_DEFAULT * (PI / 180);
	prop->angle_roll = ANGLE_ROLL_DEFAULT * (PI / 180);
	prop->clr_prop[0] = GRAPHIC_COLOR_TOP_DEFAULT;
	prop->clr_prop[1] = GRAPHIC_COLOR_BOTTOM_DEFAULT;
	prop->map_pos[AXIS_X] = WINDOW_WIDTH_DEFAULT * GRAPHIC_X_DEFAULT;
	prop->map_pos[AXIS_Y] = WINDOW_LEN_DEFAULT * GRAPHIC_Y_DEFAULT;
	prop->key_key[AXIS_ARROW] = KEY_M;
	prop->key_key[AXIS_ZOOM] = KEY_Z;
	prop->pt_scale = WINDOW_WIDTH_DEFAULT * GRAPHIC_RATIO_SURFACE_DEFAULT /
					prop->map_width;
	prop->ht_scale = prop->pt_scale * prop->ht_ratio;
	prop->clr_prop[2] = prop->map_height;
}

t_prop	*ft_fdfprop_init(void)
{
	t_prop	*prop;

	prop = (t_prop *)malloc(sizeof(t_prop));
	prop->mlx = mlx_init();
	prop->window = NULL;
	prop->pt_scale = 0;
	prop->ht_scale = 0;
	prop->clr_prop[0] = GRAPHIC_COLOR_TOP_DEFAULT;
	prop->clr_prop[1] = GRAPHIC_COLOR_BOTTOM_DEFAULT;
	prop->map_width = 0;
	prop->map_height = 0;
	prop->mouse_key = 0;
	prop->mouse_pos[AXIS_X] = 0;
	prop->mouse_pos[AXIS_Y] = 0;
	return (prop);
}
