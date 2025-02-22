/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:05 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 19:44:56 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	is_palyable(t_map *map, t_vars *vars)
{
	int	i;

	flood_fill(NULL, NULL, -1, -1);
	i = flood_fill(ft_arrdup(map->map), map, map->xw_player, map->yh_player);
	if (i - 1 != map->c)
	{
		remove_enmy(vars);
	}
}

void	remove_enmy(t_vars *vars)
{
	t_map	*map;
	int		x;
	int		y;

	map = vars->map;
	y = 0;
	x = 0;
	while (map->map[y])
	{
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'X')
				map->map[y][x] = '0';
			x++;
		}
		y++;
		x = 0;
	}
}

int	put_enmy(t_vars *vars)
{
	int	max;
	int	enemies;
	int	x;
	int	y;

	max = 1;
	if (vars->width + vars->hight > 1800)
		max = 8;
	else if (vars->width + vars->hight > 1000)
		max = 4;
	enemies = random_int(1, max);
	while (enemies && vars->map->empty >= enemies)
	{
		x = random_int(32, vars->width - 32);
		y = random_int(32, vars->hight - 32);
		if (vars->map->map[y / 32][x / 32] == '0')
		{
			vars->map->map[y / 32][x / 32] = 'X';
			vars->map->empty--;
		}
		else
			enemies++;
		enemies--;
	}
	return (is_palyable(vars->map, vars), 0);
}
