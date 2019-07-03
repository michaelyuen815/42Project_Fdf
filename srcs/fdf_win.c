/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:29:08 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/24 19:29:10 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

/*
** static string array of menu
*/

char *g_menu[] =
{
	MSG_EXIT,
	MSG_RESET,
	MSG_MOVE, MSG_MOVE2, MSG_MOVE3,
	MSG_ROTA, MSG_ROTA2, MSG_ROTA3,
	MSG_ZOOM, MSG_SCALE, MSG_HEIGHT, MSG_CLRTOP, MSG_CLRBOT,
	MSG_PROJH, MSG_PROISO, MSG_PROEVA, MSG_PROPLA,
	NULL
};

/*
** function of creating control menu that indicate mode of arrow & +/-
** the printed value is determined by the property key_key in t_prop
*/

void	ft_fdfwin_submenu(int x, int y, t_prop *prop)
{
	char *tmp;

	tmp = ft_strjoin(MSG_CTRL_ARROW, \
		(prop->key_key[AXIS_ARROW] == KEY_M ? "Move" : "Rotate"));
	mlx_string_put(prop->mlx, prop->window, x, y + 30, CLR_WORD, tmp);
	ft_strdel(&tmp);
	if (prop->key_key[AXIS_ZOOM] == KEY_F)
		tmp = ft_strjoin(MSG_CTRL_PM, "Flatten");
	else if (prop->key_key[AXIS_ZOOM] == KEY_Z)
		tmp = ft_strjoin(MSG_CTRL_PM, "Zoom");
	else if (prop->key_key[AXIS_ZOOM] == KEY_HH)
		tmp = ft_strjoin(MSG_CTRL_PM, "Altitude");
	else if (prop->key_key[AXIS_ZOOM] == KEY_T)
		tmp = ft_strjoin(MSG_CTRL_PM, "Top Color");
	else if (prop->key_key[AXIS_ZOOM] == KEY_B)
		tmp = ft_strjoin(MSG_CTRL_PM, "Bottom Color");
	else
		tmp = ft_strjoin(MSG_CTRL_PM, "Unkown");
	mlx_string_put(prop->mlx, prop->window, x, y + 60, CLR_WORD, tmp);
	ft_strdel(&tmp);
}

/*
** function of printing menu
** 1. print the control menu with function (ft_fdfwin_submenu)
** 2. print menu item in oeder based on static variable g_menu
*/

void	ft_fdfwin_menu(t_prop *prop)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	x = WINDOW_WIDTH_DEFAULT * MENU_POSITION_X_DEFAULT;
	y = WINDOW_LEN_DEFAULT * MENU_POSITION_Y_DEFAULT;
	mlx_string_put(prop->mlx, prop->window, x + 30, y, CLR_WORD, MSG_HEAD);
	ft_fdfwin_submenu(x, y, prop);
	y += MENU_SPACING_DEFAULT * 3 + 20;
	while (g_menu[i])
	{
		mlx_string_put(prop->mlx, prop->window, x, y, CLR_WORD, g_menu[i++]);
		y += MENU_SPACING_DEFAULT;
	}
}

/*
** function of printing projected line
** Step 1: store difference of x & y for 2 point given in variable (len)
** Step 2: choose the greater value of len as variable (pt) for base
** Step 3: divide all lens value by pt to get the value change per base unit
** Step 4: put the pixel for every base unit with looping:
**			for x & y coordination, use len * i to calculate projected point
**			for color, use function (ft_fdfproj_color) with ratio 1 / pt * i
*/

void	ft_fdfwin_line(t_prop *prop, t_map *map1, t_map *map2)
{
	int		i;
	double	len[3];
	double	pt;

	len[AXIS_X] = (double)map2->proj[AXIS_X] - map1->proj[AXIS_X];
	len[AXIS_Y] = (double)map2->proj[AXIS_Y] - map1->proj[AXIS_Y];
	if (!len[AXIS_X] && !len[AXIS_Y])
		return ;
	i = 0;
	pt = fabs(len[AXIS_X]) >= fabs(len[AXIS_Y]) ? len[AXIS_X] : len[AXIS_Y];
	len[AXIS_CLR] = 1 / pt;
	len[AXIS_X] /= pt;
	len[AXIS_Y] /= pt;
	while (++i < (int)fabs(pt))
		mlx_pixel_put(prop->mlx, prop->window, \
		map1->proj[0] + (int)(fabs(len[0]) * i * SIGN(len[0] * pt)), \
		map1->proj[1] + (int)(fabs(len[1]) * i * SIGN(len[1] * pt)), \
		ft_fdfproj_color(map1->color, map2->color, fabs(len[AXIS_CLR]) * i));
}

/*
** function of printing projected point
** step 1: print the projected point if the coorindation is within the window
** step 2: run function (ft_fdfwin_line) to print projected line between
**			current point and next right/down point if they exist
*/

void	ft_fdfwin_pt(t_prop *prop, t_map *map)
{
	char main;

	main = map->proj[AXIS_X] >= 0 && map->proj[AXIS_X] <= WINDOW_WIDTH_DEFAULT \
	&& map->proj[AXIS_Y] >= 0 && map->proj[AXIS_Y] <= WINDOW_LEN_DEFAULT;
	if (main)
		mlx_pixel_put(prop->mlx, prop->window, \
			map->proj[AXIS_X], map->proj[AXIS_Y], map->color);
	if (map->right)
		if (main || (map->right->proj[AXIS_X] >= 0 && \
			map->right->proj[AXIS_X] <= WINDOW_WIDTH_DEFAULT && \
			map->right->proj[AXIS_Y] >= 0 && \
			map->right->proj[AXIS_Y] <= WINDOW_LEN_DEFAULT))
			ft_fdfwin_line(prop, map, map->right);
	if (map->down)
		if (main || (map->down->proj[AXIS_X] >= 0 && \
			map->down->proj[AXIS_X] <= WINDOW_WIDTH_DEFAULT && \
			map->down->proj[AXIS_Y] >= 0 && \
			map->down->proj[AXIS_Y] <= WINDOW_LEN_DEFAULT))
			ft_fdfwin_line(prop, map, map->down);
}

/*
** function of calculating the projection point and printing points and menu
** step 1: run function (mlx_clear_window) to clear the pixel in window
** step 2: run function (ft_fdfproj_init) to calculate all projected point
** step 3: run function (ft_fdfwin_pt) to print all projected point and line
** step 4: run fucntion (ft_fdfwin_menu) to create menu
*/

void	ft_fdfwin_core(t_prop *prop, t_map *map)
{
	mlx_clear_window(prop->mlx, prop->window);
	ft_fdfulits_map(prop, map, &ft_fdfproj_init);
	ft_fdfulits_map(prop, map, &ft_fdfwin_pt);
	ft_fdfwin_menu(prop);
}
