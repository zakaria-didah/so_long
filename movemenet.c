/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movemenet.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:40:19 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/20 21:17:14 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	move_up(t_vars *vars)
{
	t_map	*map;
	int		x;
	int		y;

	map = vars->map;
	x = map->xw_player;
	y = map->yh_player;
	if (map->map[y / 32 - 1][x / 32] == 'C')
		map->c--;
	else if (map->map[y / 32 - 1][x / 32] == 'X')
		end_game();
	else if (map->map[y / 32 - 1][x / 32] == 'E' && map->c == 0)
		win_game();
	else if (map->map[y / 32 - 1][x / 32] != '0')
		return (0);
	vars->data->moves++;
	map->map[y / 32][x / 32] = '0';
	map->yh_player -= 32;
	y = map->yh_player;
	map->map[y / 32][x / 32] = 'P';
	return (1);
}

int	move_down(t_vars *vars)
{
	t_map	*map;
	int		x;
	int		y;

	map = vars->map;
	x = map->xw_player;
	y = map->yh_player;
	if (map->map[y / 32 + 1][x / 32] == 'C')
		map->c--;
	else if (map->map[y / 32 + 1][x / 32] == 'X')
		end_game();
	else if (map->map[y / 32 + 1][x / 32] == 'E' && map->c == 0)
		win_game();
	else if (map->map[y / 32 + 1][x / 32] != '0')
		return (0);
	vars->data->moves++;
	map->map[y / 32][x / 32] = '0';
	map->yh_player += 32;
	y = map->yh_player;
	map->map[y / 32][x / 32] = 'P';
	return (1);
}

int	move_right(t_vars *vars)
{
	t_map	*map;
	int		x;
	int		y;

	map = vars->map;
	x = map->xw_player;
	y = map->yh_player;
	if (map->map[y / 32][x / 32 + 1] == 'C')
		map->c--;
	else if (map->map[y / 32][x / 32 + 1] == 'X')
		end_game();
	else if (map->map[y / 32][x / 32 + 1] == 'E' && map->c == 0)
		win_game();
	else if (map->map[y / 32][x / 32 + 1] != '0')
		return (0);
	vars->data->moves++;
	map->map[y / 32][x / 32] = '0';
	map->xw_player += 32;
	x = map->xw_player;
	map->map[y / 32][x / 32] = 'P';
	return (1);
}

int	move_left(t_vars *vars)
{
	t_map	*map;
	int		x;
	int		y;

	map = vars->map;
	x = map->xw_player;
	y = map->yh_player;
	if (map->map[y / 32][x / 32 - 1] == 'C')
		map->c--;
	else if (map->map[y / 32][x / 32 - 1] == 'X')
		end_game();
	else if (map->map[y / 32][x / 32 - 1] == 'E' && map->c == 0)
		win_game();
	else if (map->map[y / 32][x / 32 - 1] != '0')
		return (0);
	vars->data->moves++;
	map->map[y / 32][x / 32] = '0';
	map->xw_player -= 32;
	x = map->xw_player;
	map->map[y / 32][x / 32] = 'P';
	return (1);
}
