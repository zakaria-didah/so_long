/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:31:48 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 19:31:40 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_img	*put__img(t_img *src, int w, int h)
{
	int		i;
	int		j;
	t_img	*dst;

	dst = new_img(32, 32, (*get_vars()));
	i = 0;
	while (i < src->w)
	{
		j = 0;
		while (j < src->h)
		{
			put_pixel_img(dst, i, j, get_pixel_img(src, w, h));
			j++;
		}
		i++;
	}
	return (dst);
}

t_vars	*new_window(int w, int h, char *str)
{
	void	*mlx_ptr;
	t_vars	*vars;

	vars = *get_vars();
	mlx_ptr = mlx_init();
	vars->game_state = start;
	vars->mlx = mlx_ptr;
	vars->win = mlx_new_window(mlx_ptr, w, h, str);
	vars->width = w;
	vars->hight = h;
	return (vars);
}

void	destroy_image(void *img)
{
	if (img)
		mlx_destroy_image((*get_vars())->mlx, img);
}

void	reset(t_vars *vars)
{
	t_map	*map;

	map = vars->map;
	map->map = ft_arrdup(map->map2);
	map->c = 0;
	map->empty = 0;
	valid_obj(map->map, &map->c, &map->empty);
	valid_player(map->map, map);
	put_enmy(vars);
}

t_vars	**get_vars(void)
{
	static t_vars	*vars;

	if (!vars)
		vars = ft_calloc(sizeof(t_vars), 1);
	return (&vars);
}
