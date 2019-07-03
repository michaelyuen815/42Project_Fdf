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

/*
** function of exit program
*/

int		ft_main_exit(void)
{
	exit(0);
	return (1);
}

/*
** function of printing error message with error output
*/

void	ft_main_printerr(char *msg)
{
	ft_putendl_fd(msg, 2);
}

/*
** function of setup graphic program window which includes:
** 1. setup window
** 2. run calculation & projection of graphic and print menu
** 3. setup react function (key & mouse)
*/

void	ft_fdfmain_win(t_prop *prop, t_map *map, char *file)
{
	if (ft_strrchr(file, '/'))
		file = ft_strrchr(file, '/') + 1;
	prop->window = mlx_new_window(\
	prop->mlx, WINDOW_WIDTH_DEFAULT, WINDOW_LEN_DEFAULT, file);
	ft_fdfwin_core(prop, map);
	ft_fdfctrl_init(prop);
}

/*
** main function of fdf
** 1. setup object of graphic properties (ft_fdfprop_init)
** 2. read source file to setup map object (ft_fdfread_main)
** 3. recalulate the properties between object details (ft_fdfprop_init2)
** 4. run setup graphic porgram function (ft_fdfmain_win)
*/

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
