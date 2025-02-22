/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:51:05 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 21:26:24 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	flood_fill(char **lines, t_map *map, int y, int x)
{
	static int	i = 0;

	if (x < 0 || y < 0)
		return (i = 0, 0);
	if (!lines[x] || !lines[x][y])
		return (i);
	if (lines[x][y] == 'E')
	{
		lines[x][y] = '*';
		return (i++);
	}
	if (lines[x][y] == '*' || lines[x][y] == '1' || lines[x][y] == 'X')
		return (i);
	if (lines[x][y] == '0')
		map->empty++;
	else if (lines[x][y] == 'C')
		i++;
	lines[x][y] = '*';
	flood_fill(lines, map, y, x + 1);
	flood_fill(lines, map, y + 1, x);
	flood_fill(lines, map, y, x - 1);
	flood_fill(lines, map, y - 1, x);
	return (i);
}

void	ft_trim_n(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
}

char	**open_read(char *s)
{
	char	*tmp;
	char	**lines;

	int (fd);
	tmp = NULL;
	lines = NULL;
	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (strerror(2), free_garb(), exit(1), NULL);
	tmp = get_next_line(fd);
	while (tmp)
	{
		ft_trim_n(tmp);
		lines = ft_arrjoin(lines, tmp);
		ft_remove(tmp);
		tmp = get_next_line(fd);
	}
	if (!lines || !valid_map(lines, ft_arrlen(lines) - 1))
	{
		ft_putstr(": try to set the walls correctly\n");
		free_garb();
		return (exit(1), NULL);
	}
	return (lines);
}

int	win_game(void)
{
	t_vars	*vars;
	t_map	*map;
	t_img	*img;

	vars = *get_vars();
	vars->game_state = end;
	vars->data->moves = 0;
	map = vars->map;
	img = new_img(vars->width, vars->hight, vars);
	mlx_clear_window(vars->mlx, vars->win);
	fill_screen(img, 0xAD99AC);
	if (vars->width >= 720 && vars->hight >= 544)
		big_screen_win(vars, img, map);
	else
	{
		mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);
		mlx_string_put(vars->mlx, vars->win, vars->width / 2 - 32, vars->hight
			/ 4, 0xFFFFFF, "You Win");
		mlx_do_sync(vars->mlx);
		sleep(3);
		_close();
	}
	return (true);
}

int	end_game(void)
{
	t_vars	*vars;
	t_img	*img;
	t_img	*dead;

	vars = *get_vars();
	if (vars->width >= 720 && vars->hight >= 544)
	{
		dead = new_file_img("textures/dead_end.xpm", vars);
		big_screen(vars, img, dead);
	}
	else
	{
		mlx_clear_window(vars->mlx, vars->win);
		mlx_string_put(vars->mlx, vars->win, vars->width / 2 - 32, vars->hight
			/ 4, 0xFFFFFF, "Game Over");
		mlx_do_sync(vars->mlx);
		sleep(3);
		_close();
	}
	return (1);
}
