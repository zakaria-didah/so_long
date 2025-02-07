/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:44:12 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/07 15:05:40 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# define p ft_printf_fd

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	int		c;
	int		empty;
	int		x_player;
	int		y_player;
	int		x;
	int		y;
	char	**map;
	void	*right_corner;
	void	*right_down_corner;
	void	*left_corner;
	void	*left_down_corner;
	void	*top_wall;
	void	*bottom_wall;
	void	*right_wall;
	void	*left_wall;
	void	*coin;
	void	*exit;
	void	*player;
	void	*enemy;

}			t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	*img;
	t_map	**map;
}			t_vars;


int			set_walls(t_vars *vars, t_map *map);
int			flood_fill(char **lines, t_map *map, int x, int y);
void		ft_error(char *s);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);
void		draw_circle(t_data *data, int x, int y, int r, int color);
void		draw_square(t_data *data, int x, int y, int size, int color);
void		draw_triangle(t_data *data, int x1, int y1, int x2, int y2, int x3,
				int y3, int color);
void		draw_rectangle(t_data *data, int x, int y, int width, int height,
				int color);
void		draw_ellipse(t_data *data, int x, int y, int a, int b, int color);
int			keycode(int keycode, t_vars *vars);
int			_close(t_vars *vars);
int			valid(char *s);
int			valid_map(char **lines, int len);
int			print_play(t_vars *vars);
void		start_the_game(t_vars *vars);
int			ft_printf_fd(int fd, const char *format, ...);
int			valid_ext(char *s);
void		init(t_vars *vars);
int			validate(t_map *map, int ac, char *av[]);

#endif