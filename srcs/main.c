/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 17:17:56 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/21 17:18:40 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

int		ft_main_exit(void)
{
	exit(0);
	return (1);
}

void	ft_main_printerr(char *msg)
{
	ft_putendl_fd(msg, 2);
}

void	ft_fdfmain_win(t_prop *prop, t_map *map, char *file)
{
	if (ft_strrchr(file, '/'))
		file = ft_strrchr(file, '/') + 1;
	prop->window = mlx_new_window(\
	prop->mlx, WINDOW_WIDTH_DEFAULT, WINDOW_LEN_DEFAULT, file);
	ft_fdfwin_core(prop, map);
	mlx_key_hook(prop->window, &ft_fdfctrl_key, prop);
	ft_fdfctrl_init(prop);
}

int		main(int ac, char **av)
{
	t_prop	*prop;
	t_map	*map;

	if (ac == 2)
	{
		prop = ft_fdfprop_init();
		map = ft_fdfread_main(prop, av[1]);
		if (map)
		{
			prop->map = map;
			ft_fdfprop_init2(prop);
			ft_fdfmain_win(prop, map, av[1]);
			mlx_loop(prop->mlx);
		}
		else
			ft_main_printerr(ERR_OPEN_FILE);
	}
	else
		ft_main_printerr(ERR_MISS_PARA);
	return (0);
}
