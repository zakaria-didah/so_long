/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:36:17 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 21:14:41 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	lunch_btn(int keycode, t_vars *vars)
{
	if (keycode == 65293 && vars->game_state == start)
	{
		mlx_clear_window(vars->mlx, vars->win);
		lunch_game();
	}
	return (true);
}

int	keycode(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape || keycode == 17)
		_close();
	if (vars->game_state == play)
	{
		if (keycode == XK_Up)
			move_up(vars);
		else if (keycode == XK_Down)
			move_down(vars);
		else if (keycode == XK_Right)
			move_right(vars);
		else if (keycode == XK_Left)
			move_left(vars);
	}
	return (true);
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->line_len) + (x * img->bpp
				/ 8))));
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img->w && y < img->h)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	check_len(char **lines)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(lines[0]);
	while (lines[i])
	{
		if ((int)ft_strlen(lines[i]) != j)
			return (ft_putstr("\n"), free_garb(), exit(1));
		i++;
	}
	if (i >= j)
		return (ft_putstr("\n"), free_garb(), exit(1));
}
