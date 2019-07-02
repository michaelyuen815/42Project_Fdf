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

void	ft_fdfwin_core(t_prop *prop, t_map *map)
{
	mlx_clear_window(prop->mlx, prop->window);
	ft_fdfulits_map(prop, map, &ft_fdfproj_init);
	ft_fdfulits_map(prop, map, &ft_fdfwin_pt);
	ft_fdfwin_menu(prop);
}
