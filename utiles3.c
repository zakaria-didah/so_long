/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:37:08 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 21:36:34 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_putstr(char *s)
{
	int	i;

	i = write(2, "Error\n", 6);
	i += write(2, "Invalid map", 11);
	i += write(2, s, ft_strlen(s));
	return (i);
}

void	big_screen_win(t_vars *vars, t_img *img, t_map *map)
{
	put_img_to_img(img, map->player_stand, vars->width / 2
		- map->player_stand->w / 2, vars->hight / 2 - map->player_stand->h / 2);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);
	mlx_string_put(vars->mlx, vars->win, vars->width / 2 - 32, vars->hight / 4,
		0xFFFFFF, "You Win");
	mlx_string_put(vars->mlx, vars->win, vars->width - vars->width / 3,
		vars->hight - vars->hight / 6, 0xFFFFFF, "Try again? press R");
	mlx_string_put(vars->mlx, vars->win, vars->width / 8, vars->hight
		- vars->hight / 6, 0xFFFFFF, "Exit? press ESC");
	mlx_do_sync(vars->mlx);
	mlx_hook(vars->win, 2, 1L << 0, end_btn, vars);
}

void	big_screen(t_vars *vars, t_img *img, t_img *dead)
{
	vars->game_state = end;
	vars->data->moves = -1;
	img = new_img(vars->width, vars->hight, vars);
	mlx_clear_window(vars->mlx, vars->win);
	put_img_to_img(img, dead, vars->width / 2 - dead->w / 2, vars->hight / 2
		- dead->h / 2);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);
	mlx_do_sync(vars->mlx);
	mlx_string_put(vars->mlx, vars->win, vars->width / 2, vars->hight / 4,
		0xFFFFFF, "Game Over");
	mlx_string_put(vars->mlx, vars->win, vars->width - vars->width / 4,
		vars->hight - vars->hight / 5, 0xFFFFFF, "Try again? press R");
	mlx_string_put(vars->mlx, vars->win, vars->width / 6, vars->hight
		- vars->hight / 5, 0xFFFFFF, "Exit? press ESC");
	mlx_hook(vars->win, 2, 1, end_btn, vars);
}

int	end_btn(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		_close();
	else if (keycode == XK_r && vars->game_state == end)
		lunch_game();
	return (1);
}

void	check_1(t_vars *vars, t_map *map, t_img *base_img)
{
	int	w;
	int	h;
	int	hight;
	int	width;

	w = 0;
	h = 0;
	hight = vars->hight;
	width = vars->width;
	if ((w && h) && (w < width && h < hight))
		if (map->map[h / 32][w / 32] == '1')
			put_img_to_img(base_img, map->inside_wall, w, h);
}
