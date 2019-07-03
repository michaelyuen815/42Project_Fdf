/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 20:37:36 by chyuen            #+#    #+#             */
/*   Updated: 2019/06/24 20:37:38 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

/*
** Mapping function that apply pointer function (*f) with all nodes in t_map
*/

void	ft_fdfulits_map(t_prop *prop, t_map *map, void (*f)(t_prop*, t_map*))
{
	t_map *cur_r;
	t_map *cur_d;

	if (!map)
		return ;
	cur_d = map;
	while (cur_d)
	{
		cur_r = cur_d;
		while (cur_r)
		{
			f(prop, cur_r);
			cur_r = cur_r->right;
		}
		cur_d = cur_d->down;
	}
}
