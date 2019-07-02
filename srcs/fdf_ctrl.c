/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ctrl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 23:18:53 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/26 23:18:54 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

int		ft_fdfctrl_mouse(int x, int y, void *param)
{
	t_prop *prop;

	prop = (t_prop *)param;
	if (prop->mouse_key == MOUSE_LEFT)
		ft_fdfctrlmouse_move(x, y, prop);
	else if (prop->mouse_key == MOUSE_RIGHT)
		ft_fdfctrelmouse_rotate(x, y, prop);
	if (prop->mouse_key)
		ft_fdfwin_core(prop, prop->map);
	return (1);
}

int		ft_fdfctrl_press(int button, int x, int y, void *param)
{
	t_prop *prop;

	prop = (t_prop *)param;
	prop->mouse_key = button;
	prop->mouse_pos[AXIS_X] = x;
	prop->mouse_pos[AXIS_Y] = y;
	return (1);
}

int		ft_fdfctrl_release(int button, int x, int y, void *param)
{
	t_prop *prop;

	(void)button;
	(void)x;
	(void)y;
	prop = (t_prop *)param;
	if (prop->mouse_key)
		prop->mouse_key = 0;
	return (1);
}

int		ft_fdfctrl_key(int key, void *param)
{
	t_prop *prop;

	prop = (t_prop *)param;
	if (BL_KEY_ARROW(key))
		prop->key_key[AXIS_ARROW] = key;
	else if (BL_KEY_ZOOM(key))
		prop->key_key[AXIS_ZOOM] = key;
	else
	{
		if (key == KEY_ESC)
			ft_main_exit();
		else if (key == KEY_F5)
			ft_fdfprop_init2(prop);
		else if (BL_ZOOM(key))
			ft_fdfctrlkey_zoom(BL_PLUS(key), prop->key_key[AXIS_ZOOM], prop);
		else if (BL_ARROW(key))
			ft_fdfctrlkey_move(key, prop->key_key[AXIS_ARROW], prop);
		else if (BL_PROJ(key))
			ft_fdfproj_std(key, prop);
	}
	ft_fdfwin_core(prop, prop->map);
	return (1);
}

void	ft_fdfctrl_init(t_prop *prop)
{
	mlx_do_key_autorepeatoff(prop->mlx);
	mlx_hook(prop->window, 2, 0, ft_fdfctrl_key, prop);
	mlx_hook(prop->window, 4, 0, ft_fdfctrl_press, prop);
	mlx_hook(prop->window, 5, 0, ft_fdfctrl_release, prop);
	mlx_hook(prop->window, 6, 0, ft_fdfctrl_mouse, prop);
	mlx_hook(prop->window, 17, 0, ft_main_exit, prop);
}
