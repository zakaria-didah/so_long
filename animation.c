/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:32:05 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 21:52:40 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	app_animation(t_vars *vars, t_img *currnt)
{
	t_img	*img;
	t_map	*map;
	int		x;
	int		y;

	x = 0;
	y = 0;
	map = vars->map;
	img = vars->data->img;
	while (map->map[y])
	{
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'C')
				put_img_to_img(img, currnt, x * 32, y * 32);
			x++;
		}
		y++;
		x = 0;
	}
}

int	animate_coin(t_vars *vars, t_map *map, float elapsed_time)
{
	static int		delay = 0;
	static clock_t	last_update = 0;
	const float		frame_time = 0.1f;
	clock_t			current_time;
	t_img			*coin_states[4];

	coin_states[0] = map->coin;
	coin_states[1] = map->coin2;
	coin_states[2] = map->coin3;
	coin_states[3] = map->coin4;
	current_time = clock();
	elapsed_time = (float)(current_time - last_update) / CLOCKS_PER_SEC;
	if (elapsed_time >= frame_time)
	{
		app_animation(vars, coin_states[delay]);
		delay = (delay + 1) % 4;
		last_update = current_time;
	}
	return (1);
}

void	set_img(t_vars *vars, t_img *img)
{
	t_map	*map;

	int (w), (h) = 0, (hight) = vars->hight, (width) = vars->width;
	w = 0;
	map = vars->map;
	while (h < hight)
	{
		while (w < width)
		{
			if ((h && w) && (h < hight && w < width))
			{
				if (map->map[h / 32][w / 32] == 'E')
					put_img_to_img(img, map->exit, w, h);
				else if (map->map[h / 32][w / 32] == 'P')
					put_img_to_img(img, map->player, w, h);
				else if (map->map[h / 32][w / 32] == '0')
					put_img_to_img(img, map->ground, w, h);
				else if (map->map[h / 32][w / 32] == 'X')
					put_img_to_img(img, map->enemy, w, h);
			}
			w += 32;
		}
		h += 32;
		w = 0;
	}
}

int	render(t_vars *vars)
{
	t_img	*img;

	if ((*get_vars())->game_state != play)
		return (1);
	img = vars->data->img;
	set_img(vars, img);
	animate_coin(vars, vars->map, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);
	mlx_set_font(vars->mlx, vars->win, "12x24");
	mlx_string_put(vars->mlx, vars->win, 10, 21, 0xD1C2CF,
	ft_itoa(vars->data->moves));
	mlx_do_sync(vars->mlx);
	return (true);
}
