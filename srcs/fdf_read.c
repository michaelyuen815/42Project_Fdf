/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:18:40 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/23 17:19:05 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"

int		ft_fdfread_height(char **line, int *color)
{
	int		ret;
	int		tmp;
	char	neg;

	ret = 0;
	neg = **line == '-';
	if (neg)
		(*line)++;
	while (ft_isdigit(**line))
		ret = ret * 10 + *(*line)++ - '0';
	if (**line == ',')
	{
		tmp = 0;
		(*line) += 3;
		while (**line && !BL_SP(**line))
			tmp = tmp * 16 + ft_strchr(HEX, *(*line)++) - HEX;
		*color = tmp;
	}
	ret *= (neg ? -1 : 1);
	while (BL_SP(**line))
		(*line)++;
	return (ret);
}

t_map	*ft_fdfread_create(t_prop *prop, int x, int y, char **line)
{
	t_map	*new;
	int		z;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	new->axis[AXIS_X] = x;
	new->axis[AXIS_Y] = y;
	new->color = 0;
	new->clr_manual = 0;
	new->axis[AXIS_Z] = ft_fdfread_height(line, &new->color);
	if (new->color)
		new->clr_manual = 1;
	new->proj[AXIS_X] = 0;
	new->proj[AXIS_Y] = 0;
	new->right = NULL;
	new->down = NULL;
	z = new->axis[AXIS_Z];
	prop->map_height = z * SIGN(z) > prop->map_height ? \
			z * SIGN(z) : prop->map_height;
	return (new);
}

t_map	*ft_fdfread_fill(t_prop *prop, t_map *pre, char *line)
{
	int		x;
	int		y;
	t_map	*new;
	t_map	*cur;

	x = 0;
	y = pre ? pre->axis[AXIS_Y] + 1 : 0;
	cur = ft_fdfread_create(prop, x++, y, &line);
	new = cur;
	while (*line)
	{
		if (!ft_isdigit(*line) && *line != '-')
			return (NULL);
		new->right = ft_fdfread_create(prop, x++, y, &line);
		new = new->right;
		if (pre)
			pre = pre->right;
		if (pre)
			pre->down = new;
	}
	prop->map_width = (x > prop->map_width ? x : prop->map_width);
	prop->map_len = y;
	return (cur);
}

t_map	*ft_fdfread_main(t_prop *prop, char *filename)
{
	int		fd;
	char	*line;
	t_map	*map;
	t_map	*cur;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = NULL;
	cur = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!map)
			map = ft_fdfread_fill(prop, map, line);
		else
			cur->down = ft_fdfread_fill(prop, cur, line);
		cur = cur ? cur->down : map;
		free(line);
		if (!cur)
			break ;
	}
	close(fd);
	if (cur)
		return (map);
	return (NULL);
}
