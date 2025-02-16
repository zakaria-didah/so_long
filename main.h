/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:44:12 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/16 10:34:55 by zdidah           ###   ########.fr       */
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
//# include <X11/keysymdef.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef enum e_bool
{
	false,
	true
}				t_bool;

# define p ft_printf_fd
typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_img;

typedef struct s_data
{
	t_img		*base_img;
	t_img		*img;
}				t_data;

typedef struct s_map
{
	int			c;
	int			empty;
	int			x_player;
	int			y_player;
	int			x;
	int			y;
	char		**map;

	t_img		*top_wall;
	t_img		*bottom_wall;
	t_img		*right_wall;
	t_img		*left_wall;
	t_img		*down_right_corner;
	t_img		*down_left_corner;
	t_img		*inside_wall;
	t_img		*ground;

	t_img		*coin;
	t_img		*coin2;
	t_img		*coin3;
	t_img		*coin4;

	t_img		*enemy;
	t_img		*enemy2;
	t_img		*enemy3;
	t_img		*enemy4;

	t_img		*exit;
	t_img		*player;

}				t_map;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			width;
	int			hight;
	t_data		*data;
	t_map		*map;
}				t_vars;

t_vars			**get_vars(void);
t_img			*merge_img(t_img *dst, t_img *src, int x, int y);
int				set_walls(t_vars *vars, t_map *map);
int				flood_fill(char **lines, t_map *map, int x, int y);
void			ft_error(char *s);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_line(t_data *data, int x1, int y1, int x2, int y2,
					int color);
void			draw_circle(t_data *data, int x, int y, int r, int color);
void			draw_square(t_data *data, int x, int y, int size, int color);
void			draw_triangle(t_data *data, int x1, int y1, int x2, int y2,
					int x3, int y3, int color);
void			draw_rectangle(t_data *data, int x, int y, int width,
					int height, int color);
void			draw_ellipse(t_data *data, int x, int y, int a, int b,
					int color);
int				keycode(int keycode, t_vars *vars);
int				_close(t_vars *vars);
int				valid(char *s);
int				valid_map(char **lines, int len);
int				print_play(t_vars *vars);
void			start_the_game(t_vars *vars);
int				ft_printf_fd(int fd, const char *format, ...);
int				valid_ext(char *s);
void			init(t_vars *vars);
int				validate(t_map *map, int ac, char *av[]);

// ... mlx healpers ..
t_vars			*new_window(int w, int h, char *str);
t_img			*new_img(int w, int h, t_vars *window);
t_img			*new_file_img(char *path, t_vars *window);
void			destroy_image(void *mlx, t_img *img);
void			put_pixel_img(t_img *img, int x, int y, int color);
void			put_img_to_img(t_img *dst, t_img *src, int x, int y);
unsigned int	get_pixel_img(t_img *img, int x, int y);


// ... mlx events ...

void			move_up(void);
void			move_down(void);
void			move_right(void);
void			move_left(void);
int				set_walls(t_vars *vars, t_map *map);
void			render(t_vars *vars);

#endif