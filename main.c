#include "get_next_line.h"
#include "main.h"


int	_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	keycode(int keycode, t_vars *vars)
{
	if (keycode == 53)
		_close(vars);
	return (0);
}

int	flood_fill(char **lines, t_map *map , int x , int y)
{
	int i = 0;
	if (!lines[x] || !lines[x][y])
		return i;
	if (lines[x][y] == '*' || lines[x][y] == '1' )
		return i;
	if(lines[x][y] == '0')
		map->empty++;
	else if(lines[x][y] == 'C')
		map->c++;
	lines[x][y] = '*';
	i++;
	i += flood_fill(lines,map, x, y+1);
	i += flood_fill(lines,map, x+1, y);
	i += flood_fill(lines,map, x, y-1);
	i += flood_fill(lines,map, x-1, y);
	return i;
}

int	print_play(t_vars *vars)
{
	int	i;
	int	j;

	i = 280;
	j = 300;
	while (i < 400)
	{
		mlx_pixel_put(vars->mlx, vars->win, j, i, 0x00FFFFFF);
		mlx_pixel_put(vars->mlx, vars->win, j + 1, i++, 0x00FFFFFF);
	}
	i = 280;
	while (j < 350)
	{
		while (j < 350)
		{
			mlx_pixel_put(vars->mlx, vars->win, j, i, 0x00FFFFFF);
			mlx_pixel_put(vars->mlx, vars->win, j++, i + 1, 0x00FFFFFF);
		}
		i = 330;
		j = 300;
		while (j < 352)
		{
			mlx_pixel_put(vars->mlx, vars->win, j, i, 0x00FFFFFF);
			mlx_pixel_put(vars->mlx, vars->win, j++, i + 1, 0x00FFFFFF);
		}
	}
	i = 280;
	j = 350;
	while (i < 330)
	{
		mlx_pixel_put(vars->mlx, vars->win, j, i, 0x00FFFFFF);
		mlx_pixel_put(vars->mlx, vars->win, j + 1, i++, 0x00FFFFFF);
	}
	return (0);
}

int	valid_map(char **lines, int len)
{
	int	(i),(d),(j);

	i = 0;
	d = 0;
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

int valid_player(char ** lines, t_map *map){
	int player, i, j;
	player = 0;
	i = 0;
	j = 0;
	while (lines[i] && lines[i][j])
	{
		if (lines[i][j] == 'P' && player == 1)
			return (p(2, "Invalid map: more then 1 player at line %d Col %d\n", i, j),0);
		else if (lines[i][j] == 'P' && player == 0){
			player = 1;
			map->x_player = i;
			map->y_player = j;
		}
		else if (lines[i][j] == '\n' ){
			j = 0;
			i++;
		}
		else if (lines[i][j] != '\n' && lines[i][j] != 'C' && lines[i][j] != 'E' && lines[i][j] != '0' && lines[i][j] != '1'){
			return (p(2, "Invalid map at line %d Col %d.\n", i, j) ,0);
		}
		j++;
	}
	if (player == 0)
		return 0;
	return 1;
}

int	valid_obj(char **lines, int *C, int *empty)
{
	int	(i) ,(j), (exit);

	i = 0;
	j = 0;
	exit = 0;
	while (lines[i])
	{
		if (lines[i][j] == 'E' && exit == 1)
			return (p(2, "Invalid map: more then 1 exit\n"), 0);
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
	if ( exit == 0 || C == 0 || empty == 0)
		return (p(2, "Invalid map: missing fields, exit or collectables\n"),0);
	return (*C);
}

char	**open_read(char *s)
{
	char	*tmp;
	char	**lines;

	int(fd), (i);
	i = 0;
	tmp = NULL;
	lines = NULL;
	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (p(2, strerror(2)), NULL);
	tmp = get_next_line(fd);
	while (1)
	{
		lines = ft_arrjoin(lines, tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
	}
	if (!valid_map(lines, ft_arrlen(lines) - 1))
		return (p(2, "Invalid map: try to set the walls correctly\n"),
			NULL);
	return (lines);
}

int	valid(char *s)
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
	p(2, "Invalid file extension or file\n");
	return (0);
}

int	validate(t_map *map, int ac, char *av[])
{
	int c = 0;
	int empty = 0;
	int i = 0;

	if (ac != 2)
		return (p(2, "Invalid number of arguments\n"), 0);
	if (!valid(av[1]))
		return (0);
	map->map = open_read(av[1]);
	if (!map->map)
		return (0);
	if (!valid_obj(map->map, &c, &empty))
		return (p(2, "Invalid map: try to set the objects correctly\n"),
			0);
	if (!valid_player(map->map, map))
		return (0);
	i = flood_fill(map->map,map, map->x_player,map->y_player);
	if (c + 2 != map->c + 2)
		return (p(2,"Invalid map: the player must have a way out to all the coins and the exit.\n"), 0);
	map->y = ft_arrlen(map->map) * 64;
	map->x = ft_strlen(map->map[0]) * 64;
	return (1);
}

int	main(int ac, char *av[])
{
	t_vars	vars;
	t_data	img ;
	t_map map = {0,0,0,0,0,0, NULL};
	int		offset;
	int		i;
	int		j;
	int		ii = 0;
	int		ij = 0;

	if (!validate(&map , ac, av))
		return (0);
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, map.x, map.y, "toby!");
	img.img = mlx_new_image(vars.mlx, map.x, map.y);

	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 64, 64); 
	void *image = mlx_xpm_file_to_image(vars.mlx, "textures/wall.xpm",  &map.x, &map.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	offset = (map.y * img.line_length + map.x * (img.bits_per_pixel / 8));
	//my_mlx_pixel_put(image, 5, 5, 0x0000FF00);
	// mlx_xpm_file_to_image(vars.mlx, "textures/play.xpm", &x, &y);
	//mlx_put_image_to_window(vars.mlx, vars.win, image, map.x , map.y);
	void *pac = mlx_png_file_to_image(vars.mlx, "textures/pac man/pac man & life counter & death/pac man/pac_man_0.png", &ii , &ij);
	mlx_put_image_to_window(vars.mlx, vars.win, pac, 400, 400);
	mlx_string_put(vars.mlx, vars.win, , , 0x00FFFFFF, "Hello World!");
	//print_play(&vars);
	// while (j < 800)
	//     mlx_pixel_put(vars.mlx, vars.win, j++ , i , 0x00FF0000);

	mlx_key_hook(vars.win, keycode, &vars);  
	mlx_hook(vars.win, 17, 0, _close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
