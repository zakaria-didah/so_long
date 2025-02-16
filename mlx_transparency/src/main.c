/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by you-              #+#    #+#             */
/*   Updated: 2025/02/09 10:09:34 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/utils.h"
#include <signal.h>

int stop_serv = 0;

void sig_handler() {
	stop_serv = 42;
	printf("Signal recieved, for now... exit without free\n");
	exit(1);
}

int	keycode(int keycode, t_win *tutorial)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 65293)
	{
		mlx_clear_window(tutorial->mlx_ptr, tutorial->win_ptr);
		//exit(0);
	}
	return (0);
}

int main(void)
{
 	t_win	tutorial;
	t_img	base_image;
	t_img	bg;
	t_img	ring;

	signal(SIGINT, sig_handler);
	tutorial = new_window(1000, 650, "transparency");
	if (!tutorial.win_ptr)
		return (2);
	base_image = new_img(1000, 650, tutorial);

	{
		bg = new_file_img("lotr_map.xpm", tutorial);
		if (!bg.img_ptr)
			return (2);
		put_img_to_img(base_image, bg, 0, 0);
	}
	{
		ring = new_file_img("ring.xpm", tutorial);
		if (!ring.img_ptr)
			return (2);
		put_img_to_img(base_image, ring, 50, 100);
	}
	mlx_put_image_to_window (base_image.win.mlx_ptr, base_image.win.win_ptr, base_image.img_ptr, 0, 0);
	mlx_key_hook(tutorial.win_ptr, keycode, &tutorial);
	mlx_loop(tutorial.mlx_ptr);
	mlx_destroy_window(tutorial.mlx_ptr, tutorial.win_ptr);
	return (0);
}
