#include "main.h"

int	_close(t_vars *vars)
{
	// mlx_destroy_image(vars->mlx, (*vars->map)->right_corner);
	// mlx_destroy_image(vars->mlx, (*vars->map)->right_down_corner);
	// mlx_destroy_image(vars->mlx, (*vars->map)->left_corner);
	// mlx_destroy_image(vars->mlx, (*vars->map)->left_down_corner);
	// mlx_destroy_image(vars->mlx, (*vars->map)->top_wall);
	// mlx_destroy_image(vars->mlx, (*vars->map)->bottom_wall);
	// mlx_destroy_image(vars->mlx, (*vars->map)->right_wall);
	// mlx_destroy_image(vars->mlx, (*vars->map)->left_wall);
	mlx_destroy_image(vars->mlx, vars->img->img);
	// mlx_destroy_image(vars->mlx, vars->(*map)->coin);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	return (free_garb(), exit(0), 0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	start_the_game(t_vars *vars)
{
	t_data	*img;
	t_map	*map;
	int		i;
	int		j;

	img = vars->img;
	map = (*vars->map);
	mlx_clear_window(vars->mlx, vars->win);
	init(vars);
	set_walls(vars, map);
	// mlx_put_image_to_window(vars->mlx, vars->win, , 0,0);
}

int	keycode(int keycode, t_vars *vars)
{
	if (keycode == 53)
		_close(vars);
	if (keycode == 36)
	{
		mlx_clear_window(vars->mlx, vars->win);
		start_the_game(vars);
	}
	return (0);
}

void	init(t_vars *vars)
{
	int		i;
	int		j;
	t_map	*map;

	i = 0;
	j = 0;
	map = (*vars->map);
	map->right_corner = mlx_xpm_file_to_image(vars->mlx,
			"textures/pac man/pac man tiles/right_corner.xpm", &i, &j);
	map->right_down_corner = mlx_xpm_file_to_image(vars->mlx,
			"textures/pac man/pac man tiles/right_down_corner.xpm", &i, &j);
	map->left_corner = mlx_xpm_file_to_image(vars->mlx,
			"textures/pac man/pac man tiles/left_corner.xpm", &i, &j);
	printf("i = %p\n", map->left_corner);
	map->left_down_corner = mlx_xpm_file_to_image(vars->mlx,
			"textures/pac man/pac man tiles/left_down_corner.xpm", &i, &j);
	map->top_wall = mlx_xpm_file_to_image(vars->mlx,
			"textures/pac man/pac man tiles/up_wall.xpm", &i, &j);
	map->bottom_wall = mlx_xpm_file_to_image(vars->mlx,
			"textures/pac man/pac man tiles/down_wall.xpm", &i, &j);
	map->right_wall = mlx_xpm_file_to_image(vars->mlx,
			"textures/pac man/pac man tiles/right_wall.xpm", &i, &j);
	map->left_wall = mlx_xpm_file_to_image(vars->mlx,"textures/pac man/pac man tiles/left_wall.png", &i, &j);
	// // map->coin = mlx_png_file_to_image(vars->mlx,
	// 		"textures/pac man/pac man tiles/coin.png", &i, &j);
	// // map->exit = mlx_png_file_to_image(vars->mlx,
	// 		"textures/pac man/pac man tiles/exit.png", &i, &j);
	// // map->player = mlx_png_file_to_image(vars->mlx,
	// 		"textures/pac man/pac man tiles/player.png", &i, &j);
	// // map->enemy = mlx_png_file_to_image(vars->mlx,
	// 		"textures/pac man/pac man tiles/enemy.png", &i, &j);
}

int	set_walls(t_vars *vars, t_map *map)
{
	int		i;
	char	**lines;
	int		j;
	int		x;
	int		y;

	i = 0;
	lines = map->map;
	j = 0;
	x = 0;
	y = 0;
	printf(" map  x = %d y = %d\n", map->x, map->y);
	while (i <= map->y)
	{
		while (j <= map->x)
		{
			if ((lines[x] && lines[x][y]) && (lines[x][y] == '1' && i > 0
					&& j > 0 && i < map->y && j < map->x))
			{
				if ((lines[x] && lines[x][y]) && (lines[x][y] == '1'
						&& lines[x][y + 1] == '1' && lines[x + 1][y] == '1'
						&& lines[x + 1][y + 1] == '1'))
				{
					printf("1 i = %d j = %d\n", i, j);
					mlx_put_image_to_window(vars->mlx, vars->win,
						map->right_corner, j, i);
				}
				else if ((lines[x] && lines[x][y]) && (lines[x][y] == '1'
						&& lines[x][y - 1] == '1' && lines[x + 1][y] == '1'
						&& lines[x + 1][y - 1] == '1'))
				{
					printf("2 i = %d j = %d\n", i, j);
					mlx_put_image_to_window(vars->mlx, vars->win,
						map->left_corner, j, i);
				}
				else if (lines[x][y] && (lines[x][y] == '1' && lines[x][y
						+ 1] == '1' && lines[x - 1][y] == '1' && lines[x - 1][y
						+ 1] == '1'))
				{
					printf("3 i = %d j = %d\n", i, j);
					mlx_put_image_to_window(vars->mlx, vars->win,
						map->right_down_corner, j, i);
				}
				else if ((lines[x] && lines[x][y]) && (lines[x][y] == '1'
						&& lines[x][y - 1] == '1' && lines[x - 1][y] == '1'
						&& lines[x - 1][y - 1] == '1'))
				{
					printf("4 i = %d j = %d\n", i, j);
					mlx_put_image_to_window(vars->mlx, vars->win,
						map->left_down_corner, j, i);
				}
				else if ((lines[x] && lines[x][y]) && (lines[x][y] == '1'
						&& lines[x][y + 1] == '1' && lines[x][y - 1] == '1'))
				{
					printf("5 i = %d j = %d\n", i, j);
					mlx_put_image_to_window(vars->mlx, vars->win, map->top_wall,
						j, i);
				}
				else if ((lines[x] && lines[x][y]) && (lines[x][y] == '1'
						&& lines[x][y + 1] == '1' && lines[x][y - 1] == '1'))
				{
					printf("6 i = %d j = %d\n", i, j);
					mlx_put_image_to_window(vars->mlx, vars->win,
						map->bottom_wall, j, i);
				}
				else if ((lines[x] && lines[x][y]) && (lines[x][y] == '1'
						&& lines[x + 1][y] == '1' && lines[x - 1][y] == '1'))
				{
					printf("7 i = %d j = %d\n", i, j);
					mlx_put_image_to_window(vars->mlx, vars->win,
						map->right_wall, j, i);
				}
				else if ((lines[x] && lines[x][y]) && (lines[x][y] == '1'
						&& lines[x + 1][y] == '1' && lines[x - 1][y] == '1'))
				{
					printf("8 i = %d j = %d\n", i, j);
					mlx_put_image_to_window(vars->mlx, vars->win,
						map->left_wall, j, i);
				}
				y++;
			}
			if (i == 0 && j == 0)
			{
				mlx_put_image_to_window(vars->mlx, vars->win, map->left_corner,
					0, 0);
			}
			else if (i == 0 && j == map->x)
			{
				mlx_put_image_to_window(vars->mlx, vars->win, map->right_corner,
					j, 0);
			}
			else if (i == map->y && j == 0)
			{
				mlx_put_image_to_window(vars->mlx, vars->win,
					map->left_down_corner, 0, i);
			}
			else if (i == map->y && j == map->x)
			{
				mlx_put_image_to_window(vars->mlx, vars->win,
					map->right_down_corner, j, i);
			}
			else if (i == 0 && (j > 0 && j < map->x))
			{
				mlx_put_image_to_window(vars->mlx, vars->win, map->top_wall, j,
					i);
			}
			else if (i == map->y && (j > 0 && j < map->x))
			{
				mlx_put_image_to_window(vars->mlx, vars->win, map->bottom_wall,
					j, i);
			}
			else if (j == 0 && (i > 0 && i < map->y))
			{
				mlx_put_image_to_window(vars->mlx, vars->win, map->left_wall, j,
					i);
			}
			else if (j == map->x && (i > 0 && i < map->y))
			{
				mlx_put_image_to_window(vars->mlx, vars->win, map->right_wall,
					j, i);
			}
			j += 32;
			printf(" --> y = %d\n", j);
		}
		printf(" --> x = %d\n", x);
		i += 32;
		x++;
		y = 0;
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
	vars = ft_calloc(sizeof(t_vars), 1);
	data = ft_calloc(sizeof(t_data), 1);
	map = ft_calloc(sizeof(t_map), 1);
	vars->map = &map;
	if (!validate(map, ac, av))
		return (free_garb(), 1);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, map->x + 32, map->y + 32, "toby!");
	data->img = mlx_new_image(vars->mlx, map->x, map->y);
	vars->img = data;
	// mlx_put_image_to_window(vars->mlx, vars->win, img->img, 64, 64);
	//image = mlx_xpm_file_to_image(vars->mlx, "textures/wall.xpm", &i, &j);
	// img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
	//		&img.line_length,
	// 		&img->endian);
	offset = (map->y * data->line_length + map->x * (data->bits_per_pixel / 8));
	printf("offset = %d\n", offset);
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
	mlx_key_hook(vars->win, keycode, vars);
	mlx_hook(vars->win, 17, 0, _close, vars);
	mlx_loop(vars->mlx);
	return (free_garb(), 0);
}
