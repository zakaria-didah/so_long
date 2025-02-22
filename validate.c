/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:40:04 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 19:50:51 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	valid_map(char **lines, int len)
{
	int (j), (i) = 0, (d) = 0;
	j = ft_strlen(lines[0]);
	check_len(lines);
	while (lines[i][d] && lines[i][d] == '1')
		d++;
	if (d != j)
		return (false);
	d = 0;
	while (lines[len][d] && lines[len][d] == '1')
		d++;
	if (d != j)
		return (false);
	i = 0;
	while (lines[i] && (lines[i][0] == '1' && lines[i][j - 1] == '1'))
		i++;
	if (i - 1 != len)
		return (false);
	return (true);
}

int	valid_player(char **lines, t_map *map)
{
	int (c), (i) = 0, (player) = false, (j) = 0;
	while (lines[i])
	{
		c = lines[i][j];
		if (lines[i][j] == 'P' && player)
			return (ft_putstr("\n"), 1);
		else if (lines[i][j] == 'P' && player == false)
		{
			player = true;
			map->xw_player = j;
			map->yh_player = i;
		}
		else if (lines[i][j] == '\0')
		{
			j = 0;
			i++;
			continue ;
		}
		else if (c != 'C' && c != 'E' && c != '0' && c != '1')
			return (ft_putstr("\n"), 1);
		j++;
	}
	if (player == false)
		return (ft_putstr(": u want to play without the player!?\n"), 1);
	return (0);
}

int	valid_obj(char **lines, int *C, int *empty)
{
	int (i), (j), (exit);
	i = 0;
	j = 0;
	exit = 0;
	while (lines[i])
	{
		if (lines[i][j] == 'E' && exit == 1)
			return (ft_putstr(": more then 1 exit\n"), 0);
		if (lines[i][j] == 'E' && exit == false)
			exit = true;
		else if (lines[i][j] == 'C')
			(*C)++;
		else if (lines[i][j] == '0')
			(*empty)++;
		else if (lines[i][j] == '\0')
		{
			j = 0;
			i++;
		}
		j++;
	}
	if (exit == false || *C == false)
		return (ft_putstr(": missing exit or coins\n"), 0);
	return (*C);
}

int	valid_ext(char *s)
{
	char	*tmp;

	if (ft_strncmp(&s[ft_strlen(s) - 4], ".ber", 5) != false)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		return (free_garb(), exit(1), false);
	}
	if (ft_strnstr(s + 1, ".ber", ft_strlen(s)))
	{
		tmp = ft_strrchr(s, '/');
		if (tmp)
		{
			if (ft_strncmp(tmp, "/.ber", ft_strlen(tmp)) != false)
				return (true);
		}
		else
			return (true);
	}
	ft_putstr_fd("Error\nInvalid file extension\n", 2);
	return (free_garb(), exit(1), 0);
}

int	validate(t_map *map, int ac, char *av[])
{
	char	**tmp;
	int		i;

	if (ac != 2)
		return (ft_putstr_fd("Error\nInvalid number of arguments\n", 2), 0);
	valid_ext(av[1]);
	map->map = open_read(av[1]);
	if (!valid_obj(map->map, &map->c, &map->empty))
		return (0);
	if (valid_player(map->map, map) == 1)
		return (0);
	tmp = ft_arrdup(map->map);
	i = flood_fill(tmp, map, map->xw_player, map->yh_player);
	if (i - 1 != map->c)
		return (ft_putstr(": Player must have \
a way out to all the coins and the exit.\n"),
			0);
	map->yh = ft_arrlen(map->map) * 32;
	map->xw = (ft_strlen(map->map[0])) * 32;
	if (map->xw > 1920 || map->yh > 1008)
		return (ft_putstr(": the map is too big\n"), 0);
	return (1);
}
