/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_proj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 20:13:47 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/24 20:13:51 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

int g_proj[][3] =
{
	{-35, 0, -45},
	{-90, 0, 0},
	{0, 0, 0}
};

/*
** function of assigned projection angles based on static varible g_proj into
**	property object t_prop
*/

void	ft_fdfproj_std(int key, t_prop *prop)
{
	key -= (BL_PROJ_PAD(key) ? KEY_1 : KEY_NUM_1);
	prop->angle_yaw = g_proj[key][0] * (PI / 180);
	prop->angle_pitch = g_proj[key][1] * (PI / 180);
	prop->angle_roll = g_proj[key][2] * (PI / 180);
}

/*
** function of changing color according to color spectrum
** the order is	1. WHITE(0xFFFFFF)
**				2. RED(0xFF0000)
**				3. YELLOW(0xFFFF00)
**				4. GREEN(0x00FF00)
**				5. LIME(0x00FFFF)
**				6. BLUE(0x0000FF)
**				7. PURPLE(0xFF00FF)
**				8. BLACK(0x000000)
*/

int		ft_fdfproj_color_set(int color, char sign)
{
	if (RED(color) == 255 && !BLU(color) && \
		!(color == CLR_RED && !sign) && !(color == CLR_YEL && sign))
		color += 0xF00 * (sign ? 1 : -1);
	else if (GRN(color) == 255 && !BLU(color) && \
		!(color == CLR_YEL && !sign) && !(color == CLR_GRN && sign))
		color += 0xF0000 * (sign ? -1 : 1);
	else if (!RED(color) && GRN(color) == 255 && \
		!(color == CLR_GRN && !sign) && !(color == CLR_LIM && sign))
		color += 0xF * (sign ? 1 : -1);
	else if (!RED(color) && BLU(color) == 255 && \
		!(color == CLR_LIM && !sign) && !(color == CLR_BLU && sign))
		color += 0xF00 * (sign ? -1 : 1);
	else if (!GRN(color) && BLU(color) == 255 && \
		!(color == CLR_BLU && !sign) && !(color == CLR_PUR && sign))
		color += 0xF0000 * (sign ? 1 : -1);
	else if (((RED(color) && !GRN(color) && BLU(color)) || \
		color == CLR_BLK) && \
		!(color == CLR_PUR && !sign) && !(color == CLR_BLK && sign))
		color += 0xF000F * (sign ? -1 : 1);
	else if (RED(color) == 255 && \
		!(color == CLR_WHITE && !sign) && !(color == CLR_RED && sign))
		color += 0xF0F * (sign ? -1 : 1);
	return (color);
}

/*
** function of calculate the projected color based on ratio
** method: calculate weighted value of every 8 bits and combine them
*/

int		ft_fdfproj_color(int clr1, int clr2, float ratio)
{
	int bits;
	int ret;

	bits = 16;
	ret = 0;
	while (bits >= 0)
	{
		ret |= (int)((float)((clr1 >> bits & 255) * (1 - ratio)) + \
		(float)((clr2 >> bits & 255) * ratio)) << bits;
		bits -= 8;
	}
	return (ret);
}

/*
** function of calculate the inital color value
** if height is 0, return bottom color value
** otherwise, calculate the ratio based on height divided by altitude of map
** run function (ft_fdfproj_color) to calculate the color with cal ratio
*/

void	ft_fdfproj_color_init(t_prop *prop, t_map *map)
{
	int		z;
	float	ratio;

	z = map->axis[AXIS_Z];
	if (!z)
	{
		map->color = prop->clr_prop[1];
		return ;
	}
	ratio = (float)z * SIGN(z) / prop->clr_prop[2];
	map->color = ft_fdfproj_color(prop->clr_prop[1], prop->clr_prop[0], ratio);
}

/*
** function of calculated project x, y coordination
*/

void	ft_fdfproj_init(t_prop *prop, t_map *map)
{
	double pre[3];
	double pos[3];
	double angle[3];

	angle[0] = prop->angle_roll;
	angle[1] = prop->angle_pitch;
	angle[2] = prop->angle_yaw;
	pre[AXIS_X] = (double)(map->axis[AXIS_X] - prop->map_width / 2) \
	* prop->pt_scale;
	pre[AXIS_Y] = (double)(map->axis[AXIS_Y] - prop->map_len / 2) \
	* prop->pt_scale;
	pre[AXIS_Z] = (double)map->axis[AXIS_Z] * prop->ht_scale;
	pos[AXIS_X] = cos(angle[0]) * pre[AXIS_X] + sin(angle[0]) * pre[AXIS_Y];
	pos[AXIS_Y] = cos(angle[0]) * pre[AXIS_Y] - sin(angle[0]) * pre[AXIS_X];
	pos[AXIS_Z] = pre[AXIS_Z];
	pre[AXIS_X] = cos(angle[1]) * pos[AXIS_X] - sin(angle[1]) * pos[AXIS_Z];
	pre[AXIS_Z] = sin(angle[1]) * pos[AXIS_X] + cos(angle[1]) * pos[AXIS_Z];
	pre[AXIS_Y] = cos(angle[2]) * pos[AXIS_Y] + sin(angle[2]) * pre[AXIS_Z];
	map->proj[AXIS_X] = (int)pre[AXIS_X] + prop->map_pos[AXIS_X];
	map->proj[AXIS_Y] = (int)pre[AXIS_Y] + prop->map_pos[AXIS_Y];
	if (!map->clr_manual)
		ft_fdfproj_color_init(prop, map);
}
