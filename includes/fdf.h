/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:39:43 by chyuen            #+#    #+#             */
/*   Updated: 2019/07/02 16:02:12 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "err_msg.h"
# include "para.h"
# include "key.h"

# define CLR_WORD I_MAX
# define CLR_WHITE 0xFFFFFF
# define CLR_RED 0xFF0000
# define CLR_YEL 0xFFFF00
# define CLR_GRN 0x00FF00
# define CLR_LIM 0x00FFFF
# define CLR_BLU 0x0000FF
# define CLR_PUR 0xFF00FF
# define CLR_BLK 0x000000
# define AXIS_X 0
# define AXIS_Y 1
# define AXIS_Z 2
# define AXIS_CLR 2
# define AXIS_ARROW 0
# define AXIS_ZOOM 1
# define PI 3.14159265

# define BL_KEY_ARROW(key) (key == KEY_M || key == KEY_R)
# define BL_KEY_ZOOM(key) (BL_KEY_SCALE(key) || key == KEY_T || key == KEY_B)
# define BL_KEY_SCALE(key) (key == KEY_F || key == KEY_Z || key == KEY_HH)
# define BL_ZOOM(key) (BL_MINUS(key) || BL_PLUS(key))
# define BL_PLUS(key) (key == KEY_PLUS || key == KEY_NUM_PLUS)
# define BL_MINUS(key) (key == KEY_MINUS || key == KEY_NUM_MINUS)
# define BL_ARROW(key) (BL_UPDN(key) || key == KEY_LEFT || key == KEY_RIGHT)
# define BL_UPDN(key) (key == KEY_UP || key == KEY_DOWN)
# define BL_PROJ(key) (BL_PROJ_PAD(key) || BL_PROJ_NUM(key))
# define BL_PROJ_PAD(key) (key >= KEY_1 && key <= KEY_END)
# define BL_PROJ_NUM(key) (key >= KEY_NUM_1 && key <= KEY_NUM_END)

# define RED(clr) (clr >> 16 & 255)
# define GRN(clr) (clr >> 8 & 255)
# define BLU(clr) (clr & 255)
# define SIGN(val) (val >= 0 ? 1 : -1)

typedef struct s_map	t_map;
typedef	struct s_prop	t_prop;

struct	s_map
{
	int		axis[3];
	int		proj[2];
	int		color;
	int		clr_manual;
	t_map	*right;
	t_map	*down;
};

struct	s_prop
{
	void	*mlx;
	void	*window;
	int		pt_scale;
	int		ht_scale;
	int		clr_prop[3];
	double	ht_ratio;
	double	angle_yaw;
	double	angle_pitch;
	double	angle_roll;
	int		map_len;
	int		map_width;
	int		map_height;
	double	map_pos[2];
	int		key_key[2];
	int		mouse_key;
	int		mouse_pos[2];
	t_map	*map;
};

int		ft_main_exit(void);

t_prop	*ft_fdfprop_init(void);
void	ft_fdfprop_init2(t_prop *prop);

t_map	*ft_fdfread_main(t_prop *prop, char *filename);

int		ft_fdfctrl_key(int key, void *param);
void	ft_fdfctrl_init(t_prop *prop);

void	ft_fdfctrlkey_zoom(int plus, int key, t_prop *prop);
void	ft_fdfctrlkey_move(int key_arrow, int key, t_prop *prop);

void	ft_fdfctrlmouse_move(int x, int y, t_prop *prop);
void	ft_fdfctrelmouse_rotate(int x, int y, t_prop *prop);

void	ft_fdfproj_init(t_prop *prop, t_map *map);
void	ft_fdfproj_std(int key, t_prop *prop);
int		ft_fdfproj_color_set(int color, char sign);
int		ft_fdfproj_color(int clr1, int clr2, float ratio);
void	ft_fdfproj_color_init(t_prop *prop, t_map *map);

void	ft_fdfwin_core(t_prop *prop, t_map *map);
void	ft_fdfwin_pt(t_prop *prop, t_map *map);

void	ft_fdfulits_map(t_prop *prop, t_map *map, void (*f)(t_prop*, t_map*));

#endif
