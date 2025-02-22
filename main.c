/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:14:16 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 21:36:16 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	start_game(void)
{
	t_vars	*vars;
	t_map	*map;
	t_img	*img;
	t_img	*tmp;

	vars = *get_vars();
	map = vars->map;
	img = new_img(vars->width, vars->hight, vars);
	tmp = new_file_img("textures/skull_scaled.xpm", vars);
	fill_screen(img, 0x877688);
	mlx_set_font(vars->mlx, vars->win, "12x24");
	if (vars->width >= 1088 && vars->hight >= 544)
	{
		put_img_to_img(img, tmp, vars->width / 4 - tmp->w, vars->hight / 2
			- tmp->h / 2);
		put_img_to_img(img, map->player_stand, (vars->width / 4) * 3,
			vars->hight / 2 - map->player_stand->h / 2);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);
	mlx_string_put(vars->mlx, vars->win, vars->width / 2 - 32, vars->hight / 2,
		0xFFFFFF, "Start");
	mlx_do_sync(vars->mlx);
	mlx_hook(vars->win, 2, 1, lunch_btn, vars);
	return (1);
}

void	init(t_vars *vars)
{
	t_map	*map;

	map = vars->map;
	map->ground = new_file_img("textures/ground.xpm", vars);
	map->player_stand = new_file_img("textures/player_standing.xpm", vars);
	map->bottom_wall = new_file_img("textures/bottom_wall.xpm", vars);
	map->inside_wall = merge_img(new_file_img("textures/inside_wall.xpm",
				vars));
	map->right_wall = new_file_img("textures/right_wall.xpm", vars);
	map->down_right = new_file_img("textures/down_right_corner.xpm", vars);
	map->left_wall = new_file_img("textures/left_wall.xpm", vars);
	map->down_left = new_file_img("textures/down_left_corner.xpm", vars);
	map->exit_game = new_file_img("textures/exit_game.xpm", vars);
	map->top_wall = new_file_img("textures/top_wall.xpm", vars);
	map->player = merge_img(new_file_img("textures/player.xpm", vars));
	map->resume = new_file_img("textures/resume.xpm", vars);
	map->enemy = merge_img(new_file_img("textures/skull_v2_1.xpm", vars));
	map->coin2 = merge_img(new_file_img("textures/coin_2.xpm", vars));
	map->coin3 = merge_img(new_file_img("textures/coin_3.xpm", vars));
	map->coin4 = merge_img(new_file_img("textures/coin_4.xpm", vars));
	map->coin = merge_img(new_file_img("textures/coin_1.xpm", vars));
	map->exit = merge_img(new_file_img("textures/exit.xpm", vars));
}

void	set_walls(t_vars *vars, t_map *map, t_img *base_img)
{
	int (w), (h) = 0, (hight) = vars->hight, (width) = vars->width;
	w = 0;
	while (h < hight)
	{
		while (w < width)
		{
			check_1(vars, map, base_img);
			if (w == 0 && h < hight - 32)
				put_img_to_img(base_img, map->left_wall, w, h);
			else if (w == 0 && h == hight - 32)
				put_img_to_img(base_img, map->down_left, w, h);
			else if (w == width - 32 && h < hight - 32)
				put_img_to_img(base_img, map->right_wall, w, h);
			else if (w == width - 32 && h == hight - 32)
				put_img_to_img(base_img, map->down_right, w, h);
			else if (h == 0 && w < width)
				put_img_to_img(base_img, map->top_wall, w, h);
			else if (h == hight - 32 && w < width)
				put_img_to_img(base_img, map->bottom_wall, w, h);
			w += 32;
		}
		h += 32;
		w = 0;
	}
}

int	lunch_game(void)
{
	static int	counter = 0;
	t_vars		*vars;
	t_map		*map;
	t_data		*data;

	vars = *get_vars();
	map = vars->map;
	data = vars->data;
	vars->game_state = play;
	if (counter > 0)
		reset(vars);
	else
		set_walls(vars, map, data->base_img);
	map->xw_player *= 32;
	map->yh_player *= 32;
	counter++;
	data->img = new_img(vars->width, vars->hight, vars);
	put_img_to_img(data->img, data->base_img, 0, 0);
	set_img(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, data->img->img_ptr, 0, 0);
	mlx_do_sync(vars->mlx);
	return (1);
}

int	main(int ac, char *av[])
{
	t_vars	*vars;
	t_data	*data;
	t_map	*map;

	data = ft_calloc(sizeof(t_data), 1);
	map = ft_calloc(sizeof(t_map), 1);
	if (!validate(map, ac, av))
		return (free_garb(), 1);
	srand(time(NULL));
	map->map2 = ft_arrdup(map->map);
	vars = new_window(map->xw, map->yh, "toby!");
	data->base_img = new_img(map->xw, map->yh, vars);
	vars->map = map;
	vars->data = data;
	init(vars);
	put_enmy(vars);
	start_game();
	mlx_loop_hook(vars->mlx, render, vars);
	mlx_hook(vars->win, 17, 0, _close, vars);
	mlx_key_hook(vars->win, keycode, vars);
	mlx_loop(vars->mlx);
	return (destroy_list(), free_garb(), 0);
}
