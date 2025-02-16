#include "main.h"

t_vars	**get_vars()
{
	static t_vars	*vars;

	if (!vars)
		vars = ft_calloc(sizeof(t_vars), 1);
	return (&vars);
}

int	_close(t_vars *vars)
{
	//mlx_destroy_image(vars->mlx, vars->map->right_corner);
	//mlx_destroy_image(vars->mlx, vars->map->right_down_corner);
	//mlx_destroy_image(vars->mlx, vars->map->left_corner);
	//mlx_destroy_image(vars->mlx, vars->map->left_down_corner);
	mlx_destroy_image(vars->mlx, vars->map->top_wall);
	mlx_destroy_image(vars->mlx, vars->map->bottom_wall);
	mlx_destroy_image(vars->mlx, vars->map->right_wall);
	mlx_destroy_image(vars->mlx, vars->map->left_wall);
	mlx_destroy_image(vars->mlx, vars->data->base_img->img_ptr);
	// mlx_destroy_image(vars->mlx, vars->(*map)->coin);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	return (free_garb(), exit(0), 0);
}

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

void	start_the_game(t_vars *vars)
{
	t_map	*map;
	int		i;
	int		j;

	map = vars->map;
	mlx_clear_window(vars->mlx, vars->win);
	set_walls(vars, map);
	// mlx_put_image_to_window(vars->mlx, vars->win, , 0,0);
}

void render(t_vars *vars)
{
	t_img *img = vars->data->img;
	mlx_clear_window(vars->mlx, vars->win);
	printf("rendering %p\n", vars->data->base_img);
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->data->base_img->img_ptr, 0, 0);	
	//put_img_to_img(img, vars->data->base_img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);
}


int	keycode(int keycode, t_vars *vars)
{



	if (keycode == XK_Escape)
		_close(vars);
	if (keycode == XK_KP_Enter)
	{
		mlx_clear_window(vars->mlx, vars->win);
		start_the_game(vars);
	}
	if (keycode == XK_Up)
	{
		move_up();
	}
	if (keycode == XK_Down)
	{
		move_down();
	}
	if (keycode == XK_Right)
	{
		move_right();
	}
	if (keycode == XK_Left)
	{
		move_left();
	}
	render(vars);

	return (0);
}

void	init(t_vars *vars)
{
	t_map	*map = vars->map;
	map->x_player *= 32;
	map->y_player *= 32;
	map->right_wall = new_file_img("textures/AnyConv.com__right_wall.xpm", vars);
	map->left_wall = new_file_img("textures/AnyConv.com__left_wall.xpm", vars);
	map->top_wall = new_file_img("textures/AnyConv.com__top_wall.xpm", vars);
	map->bottom_wall = new_file_img("textures/AnyConv.com__bottom_wall.xpm", vars);
	map->down_right_corner = new_file_img("textures/AnyConv.com__down_right_corner.xpm", vars);
	map->down_left_corner = new_file_img("textures/AnyConv.com__down_left_corner.xpm", vars);
	map->inside_wall = new_file_img("textures/inside_wall1.xpm",vars);
	map->ground = new_file_img("textures/ground.xpm",vars);
	map->inside_wall = merge_img(map->inside_wall, map->ground, 0, 0);
	map->exit = new_file_img("textures/exit.xpm",vars);
	map->enemy = new_file_img("textures/AnyConv.com__skull_v2_1.xpm",vars);
	map->coin = new_file_img("textures/AnyConv.com__coin_1.xpm",vars);
	map->coin2 = new_file_img("textures/AnyConv.com__coin_2.xpm",vars);
	map->coin3 = new_file_img("textures/AnyConv.com__coin_3.xpm",vars);
	map->coin4 = new_file_img("textures/AnyConv.com__coin_4.xpm",vars);
	map->player = new_file_img("textures/AnyConv.com__player.xpm",vars);
}

t_img *merge_img(t_img *dst, t_img *src, int x, int y)
{
	int i;
	int j;
	i = 0;
	j = 0;
	t_img *tmp = new_img( src->w, src->h, (*get_vars()));
	while (i < src->w)
	{
		while (j < src->h)
		{
			put_pixel_img(tmp, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
		j = 0;
	}
	i = 0;
	j = 0;
	while (i < dst->w)
	{
		while (j < dst->h)
		{
			put_pixel_img(tmp, x + i, y + j, get_pixel_img(dst, i, j));
			j++;
		}
		i++;
		j = 0;
	}
	return (tmp);
}

int	set_walls(t_vars *vars, t_map *map)
{

	char	**line;

	int		x;
	int size = 32;

	line = vars->map->map;
	int w;
	int h;
	int hight = vars->hight;
	int width = vars->width;

	w = 0;
	h = 0;

	x = 0;
	int y = 0 ;

	t_img *base_img = vars->data->base_img;
	t_img *tmp = new_img( map->x, map->y,vars );
	while (h < hight)
	{
		while (w < width)
		{
			if ( (h >= 0 && h < hight) && (w >= 0 && w < width) && line[x] && line[x][y]){
				if (line[x][y] == '1'){
					put_img_to_img(base_img, map->inside_wall, w, h);
				}
			}
			if ( w == 0 && h < hight - size){
				put_img_to_img(base_img, map->left_wall, w, h);
			}
			else if (w == 0 && h == hight - size){
				put_img_to_img(base_img, map->down_left_corner, w, h);
			}
			else if (w == width - size && h < hight - size ){
				put_img_to_img(base_img, map->right_wall, w, h);
			}
			else if (w == width - size && h == hight -size ){
				put_img_to_img(base_img, map->down_right_corner, w, h);
			}
			else if (h == 0 && w < width){
				put_img_to_img(base_img, map->top_wall, w, h);
			}
			else if (h == hight - size && w < width){
				put_img_to_img(base_img, map->bottom_wall, w, h);
			}
			w += size;
			y++;
		}
		h += size;
		x++;
		w = 0;
		y = 0;
	}

	return (1);
}

int animate_coin(t_vars *vars, int x, int y)
{
	t_img *img = vars->data->img;
	static int i = 0;
	if (i == 0){
		put_img_to_img(img, vars->map->ground, x, y);
		put_img_to_img(img, vars->map->coin, x, y);
	}
	else if (i == 1){
		put_img_to_img(img, vars->map->ground, x, y);
		put_img_to_img(img, vars->map->coin2, x, y);
	}
	else if (i == 2){
		put_img_to_img(img, vars->map->ground, x, y);
		put_img_to_img(img, vars->map->coin3, x, y);
	}
	else if (i == 3){
		put_img_to_img(img, vars->map->ground, x, y);
		put_img_to_img(img, vars->map->coin4, x, y);
	}
	i++;
	// usleep(500);
	if (i == 4)
		i = 0;
	return (1);
}

int set_img(t_vars *vars)
{
	int i = 0;
	int j = 0;
	int w = 0;
	t_img *img = vars->data->img;
	int h = 0;
	int hight = vars->hight;
	int width = vars->width;
	t_map *map = vars->map;
	char **line = vars->map->map;
	while (h < hight)
	{
		while (w < width)
		{
			if ( (h >= 0 && h < hight) && (w >= 0 && w < width) && line[i] && line[i][j]){

				if (line[i][j] == 'E'){
					put_img_to_img(img, map->ground, w, h);
					put_img_to_img(img, map->exit, w, h);
				}
				else if (line[i][j] == 'C'){
					animate_coin(vars, w, h);
				}
				else if (line[i][j] == 'P'){
					put_img_to_img(img, map->ground, w, h);
					put_img_to_img(img, map->player, w, h);
				}
				else if (line[i][j] == '0'){
					put_img_to_img(img, map->ground, w, h);
				}
			}
			w += 32;
			j++;
		}
		h += 32;
		i++;
		w = 0;
		j = 0;
	}
	return (1);
}

int	main(int ac, char *av[])
{
	t_vars	*vars;
	t_data	*data;
	t_map	*map;
	int		offset;
	int		ii;
	int		ij;
	void	*image;
	int btn_x, btn_y;
	int i, j;
	data = ft_calloc(sizeof(t_data), 1);
	map = ft_calloc(sizeof(t_map), 1);
	if (!validate(map, ac, av))
		return (free_garb(), 1);
	vars = new_window(map->x , map->y , "toby!");
	data->base_img = new_img( map->x, map->y,vars );
	vars->map = map;
	vars->data = data;
	init(vars);
	set_walls(vars, map);
	t_img *img = new_img( map->x, map->y,vars );
 	put_img_to_img(img, data->base_img, 0, 0);
	data->img = img;
	set_img(vars);
	//(vars->mlx, vars->win, data->base_img->img_ptr, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img_ptr, 0, 0);

	mlx_loop_hook(vars->mlx, set_img, vars);
	mlx_key_hook(vars->win, keycode, vars);
		//mlx_put_image_to_window(vars->mlx, vars->win, data->img, 64, 64);
	//image = mlx_xpm_file_to_image(vars->mlx, "textures/wall.xpm", &i, &j);
	// img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
	//		&img.line_length,
	// 		&img->endian);
	// offset = (map->y * data->line_length + map->x * (data->bits_per_pixel / 8));
	// printf("offset = %d\n", offset);
	// my_mlx_pixel_put(image, 5, 5, 0x0000FF00);
	// mlx_xpm_file_to_image(vars->mlx, "textures/play.xpm", &x, &y);
	// mlx_put_image_to_window(vars->mlx, vars->win, image, map->x , map->y);
	// void *pac = mlx_png_file_to_image(vars->mlx, "pacman.png", &ii , &ij);
	// void *lets_play_btn = mlx_png_file_to_image(vars->mlx,
	//		"lets_play_btn.png", &btn_x , &btn_y);
	// printf("x = %d y = %d\n", btn_x, btn_y);
	// mlx_put_image_to_window(vars->mlx, vars->win, data->img, map->x,map->y );
	// mlx_put_image_to_window(vars->mlx, vars->win, pac, (map->x/2) - (ii/2),
	//	(map->y/2) - (ij/2));
	// mlx_put_image_to_window(vars->mlx, vars->win, lets_play_btn, (map->x/2)
	//	- btn_x/2 , (map->y - map->y/4) - btn_y/2);
	// mlx_string_put(vars->mlx, vars->win, 100, 100, 0x00FFFFFF,
	//	"Hello World!");
	// print_play(&vars);
	// while (j < 800)
	//     mlx_pixel_put(vars->mlx, vars->win, j++ , i , 0x00FF0000);
	mlx_loop_hook(vars->mlx, set_img, vars);
	mlx_key_hook(vars->win, keycode, vars);
	mlx_hook(vars->win, 17, 0, _close, vars);
	mlx_loop(vars->mlx);
	return (free_garb(), 0);
}
