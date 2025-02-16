/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:31:48 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/16 10:54:30 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_vars	*new_window(int w, int h, char *str)
{
	void	*mlx_ptr;
	t_vars	*vars = *get_vars();

	mlx_ptr = mlx_init();
	vars->mlx = mlx_ptr;
	vars->win = mlx_new_window(mlx_ptr, w, h, str);
	vars->width = w;
	vars->hight = h;
	return (vars);
} 

t_img	*new_img(int w, int h, t_vars *window)
{
	t_img	*image = ft_calloc(sizeof(t_img), 1);

	image->img_ptr = mlx_new_image(window->mlx, w, h);
	image->addr = mlx_get_data_addr(image->img_ptr, &(image->bpp),
			&(image->line_len), &(image->endian));
	image->w = w;
	image->h = h;
	return (image);
}

t_img	*new_file_img(char *path, t_vars *window)
{
	t_img	*image = ft_calloc(sizeof(t_img), 1);

	image->img_ptr = mlx_xpm_file_to_image(window->mlx, path, &image->w, &image->h);
	if (!image->img_ptr)
		p(2, "Error\nFile [%s] could not be read\n", path);
	else{
		image->addr = mlx_get_data_addr(image->img_ptr, &(image->bpp),
				&(image->line_len), &(image->endian));
		if( !image->addr){
			p(2, "Error\nFile [%s] could not be read\n", path);
			exit(1);
		}
	}
	return (image);
}

void	destroy_image(void *mlx, t_img *img)
{
	if (img->img_ptr)
		mlx_destroy_image(mlx, img->img_ptr);
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char *dst;

	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < img->w && y < img->h)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y) {
	int i;
	int j;

	i = 0;
	while(i < src->w) {
		j = 0;
		while (j < src->h) {
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

unsigned int	get_pixel_img(t_img *img, int x, int y) {
	return (*(unsigned int *)((img->addr + (y * img->line_len) + (x * img->bpp / 8))));
}


void move_up(void){
	t_vars *vars = *get_vars();
	t_map *map = vars->map;
	t_img *img = vars->data->img;
	int x = map->x_player;
	int y = map->y_player;
	mlx_string_put(vars->mlx, vars->win, x, y, 0xffffffff, "up");
	if (map->map[y / 32 - 1][x / 32] == '1')
		return ;
	put_img_to_img(img, map->ground, x, y);
	put_img_to_img(img, map->player, x, y - 32);
	map->y_player -= 32;

}

void move_down(void){
	t_vars *vars = *get_vars();
	t_map *map = vars->map;
	t_img *img = vars->data->img;
	int x = map->x_player;
	int y = map->y_player;
	if (map->map[y / 32 + 1][x / 32] == '1')
		return ;
	put_img_to_img(img, map->ground, x, y);
	put_img_to_img(img, map->player, x, y + 32);
	map->y_player += 32;
}

void move_right(void){
	t_vars *vars = *get_vars();
	t_map *map = vars->map;
	t_img *img = vars->data->img;
	int x = map->x_player;
	int y = map->y_player;
	if (map->map[y / 32][x / 32 + 1] == '1')
		return ;
	put_img_to_img(img, map->ground, x, y);
	put_img_to_img(img, map->player, x + 32, y);
	map->x_player += 32;
}

void move_left(void){
	t_vars *vars = *get_vars();
	t_map *map = vars->map;
	t_img *img = vars->data->img;
	int x = map->x_player;
	int y = map->y_player;
	if (map->map[y / 32][x / 32 - 1] == '1')
		return ;
	put_img_to_img(img, map->ground, x, y);
	put_img_to_img(img, map->player, x - 32, y);
	map->x_player -= 32;
}
