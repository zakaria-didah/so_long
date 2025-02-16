/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:40:04 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/15 11:00:00 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	flood_fill(char **lines, t_map *map, int x, int y)
{
	int	i;

	i = 0;
	if (!lines[x] || !lines[x][y])
		return (i);
	if (lines[x][y] == '*' || lines[x][y] == '1')
		return (i);
	if (lines[x][y] == '0')
		map->empty++;
	else if (lines[x][y] == 'C')
		map->c++;
	lines[x][y] = '*';
	i++;
	i += flood_fill(lines, map, x, y + 1);
	i += flood_fill(lines, map, x + 1, y);
	i += flood_fill(lines, map, x, y - 1);
	i += flood_fill(lines, map, x - 1, y);
	return (i);
}

// TO VALIDATE THE MAP IF THE WALLS ARE CORRECTLY SET
int	valid_map(char **lines, int len)
{
	int(j), (i) = 0, (d) = 0;
	j = ft_strlen(lines[0]);
	while (lines[i])
	{
		if (ft_strlen(lines[i]) != j)
			return (0);
		i++;
	}
	i = 0;
	while (lines[i][d] && (lines[i][d] != '\n' && lines[i][d] == '1'))
		d++;
	if (d != j - 1)
		return (0);
	d = 0;
	while (lines[len][d] && (lines[len][d] != '\n' && lines[len][d] == '1'))
		d++;
	if (d != j - 1)
		return (0);
	i = 0;
	while (lines[i] && (lines[i][0] == '1' && lines[i][j - 2] == '1'))
		i++;
	if (i - 1 != len)
		return (0);
	return (1);
}

// TO VALIDATE THE PLAYER AND GET HIS POSITION
int	valid_player(char **lines, t_map *map)
{
	int(player) = 0, (i) = 0, (j) = 0;
	while (lines[i] && lines[i][j])
	{
		if (lines[i][j] == 'P' && player == 1)
			return (ft_printf_fd(2, "Invalid map: more then 1 player at line %d Col %d\n",
             i, j), 0);
		else if (lines[i][j] == 'P' && player == 0)
		{
			player = 1;
			map->x_player = i;
			map->y_player = j;
		}
		else if (lines[i][j] == '\n')
		{
			j = 0;
			i++;
		}
		else if (lines[i][j] != '\n' && lines[i][j] != 'C' && lines[i][j] != 'E'
			&& lines[i][j] != '0' && lines[i][j] != '1')
			return (ft_printf_fd(2, "Invalid map at line %d Col %d.\n", i, j),
				0);
		j++;
	}
	if (player == 0)
		return (0);
	return (1);
}

// TO VALIDATE THE OBJECTS AND GET THE NUMBER OF COLLECTABLES AND THE EXIT
int	valid_obj(char **lines, int *C, int *empty)
{
	int(i), (j), (exit);
	i = 0;
	j = 0;
	exit = 0;
	while (lines[i])
	{
		if (lines[i][j] == 'E' && exit == 1)
			return (ft_printf_fd(2, "Invalid map: more then 1 exit\n"), 0);
		if (lines[i][j] == 'E' && exit == 0)
			exit = 1;
		else if (lines[i][j] == 'C')
			(*C)++;
		else if (lines[i][j] == '0')
			(*empty)++;
		else if (lines[i][j] == '\n')
		{
			j = 0;
			i++;
		}
		j++;
	}
	if (exit == 0 || C == 0 || empty == 0)
		return (ft_printf_fd(2, "Invalid map: missing fields, exit or coins\n"),
			0);
	return (*C);
}
// TO OPEN THE FILE AND READ IT

char	**open_read(char *s)
{
	char	*tmp;
	char	**lines;

	int(fd), (i) = 0;
	tmp = NULL;
	lines = NULL;
	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (ft_printf_fd(2, strerror(2)), NULL);
	tmp = get_next_line(fd);
	while (tmp)
	{
		lines = ft_arrjoin(lines, tmp);
		ft_remove(tmp);
		tmp = get_next_line(fd);
	}
	if (!valid_map(lines, ft_arrlen(lines) - 1))
		return (ft_printf_fd(2,
				"Invalid map: try to set the walls correctly\n"), NULL);
	return (lines);
}

int	valid_ext(char *s)
{
	char	*tmp;

	if (ft_strnstr(s + 1, ".ber", ft_strlen(s)))
	{
		if (tmp = ft_strrchr(s, '/'), tmp)
		{
			if (ft_strncmp(tmp, "/.ber", ft_strlen(tmp)) != 0)
				return (1);
		}
	}
	ft_printf_fd(2, "Invalid file extension or file\n");
	exit(1);
}

int	validate(t_map *map,  int ac, char *av[])
{
	int (c) = 0, (empty) = 0, (i) = 0;
	char **tmp ;
	
	if (ac != 2)
		return (ft_printf_fd(2, "Invalid number of arguments\n"), 0);
	valid_ext(av[1]);
	map->map = open_read(av[1]);
	if (!map->map)
		return (0);
	if (!valid_obj(map->map, &c, &empty))
		return (ft_printf_fd(2,
				"Invalid map: try to set the objects correctly\n"), 0);
	if (!valid_player(map->map, map))
		return (0);
	tmp = ft_arrdup(map->map);
	i = flood_fill(tmp, map, map->x_player, map->y_player);
	if (c + 2 != map->c + 2)
		return (ft_printf_fd(2,
			"Invalid map: Player must have a way out to the coins and the exit.\n"),
			0);
	map->y = ft_arrlen(map->map) * 32;
	map->x = (ft_strlen(map->map[0]) -1 )* 32;
	if (map->x > 1920 || map->y > 1008)
		return (p(2, "Invalid map: the map is too big\n"), 0);
	return (1);
}
