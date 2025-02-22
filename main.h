/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:44:12 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 19:49:42 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define MLX_SYNC_IMAGE_WRITABLE 1
# define MLX_SYNC_WIN_FLUSH_CMD 2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

# include "get_next_line.h"
# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

typedef enum e_bool
{
	false,
	true
}				t_bool;

typedef enum e_game
{
	start,
	play = 1,
	end
}				t_game;

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
	int			moves;
}				t_data;

typedef struct s_map
{
	int			c;
	int			empty;
	int			xw_player;
	int			yh_player;
	int			xw;
	int			yh;
	char		**map;
	char		**map2;

	t_img		*top_wall;
	t_img		*bottom_wall;
	t_img		*right_wall;
	t_img		*left_wall;
	t_img		*down_right;
	t_img		*down_left;
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
	t_img		*player_anim;
	t_img		*player_stand;
	t_img		*big_skull;

	t_img		*exit_game;
	t_img		*resume;

}				t_map;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			width;
	int			hight;
	t_data		*data;
	t_map		*map;
	int			game_state;
}				t_vars;

// ... pasing ...
int				valid_obj(char **lines, int *C, int *empty);
int				valid_player(char **lines, t_map *map);
int				valid_ext(char *s);
int				valid_map(char **lines, int len);
int				valid_ext(char *s);
int				validate(t_map *map, int ac, char *av[]);
int				valid(char *s);
char			**open_read(char *s);
int				flood_fill(char **lines, t_map *map, int x, int y);

// ... img handlers ...
void			set_walls(t_vars *vars, t_map *map, t_img *base_img);
void			set_img(t_vars *vars);
void			init(t_vars *vars);

// ... utiles ...
t_vars			**get_vars(void);
t_list			**get_head_list(void);
int				flood_fill(char **lines, t_map *map, int x, int y);
int				keycode(int keycode, t_vars *vars);
int				_close(void);
int				ft_printf_fd(int fd, const char *format, ...);
int				random_int(int min, int max);
int				ft_putstr(char *s);

// ... mlx feautchers ...
void			is_palyable(t_map *map, t_vars *vars);
int				put_enmy(t_vars *vars);
int				lunch_game(void);
int				win_game(void);
void			reset(t_vars *vars);
int				end_btn(int keycode, t_vars *vars);
int				lunch_btn(int keycode, t_vars *vars);
int				start_game(void);
int				end_game(void);
int				animate_coin(t_vars *vars, t_map *map);

// ... mlx healpers ..
t_img			*merge_img(t_img *dst);
t_img			*dup_img(t_img *img);
t_vars			*new_window(int w, int h, char *str);
t_img			*new_img(int w, int h, t_vars *window);
t_img			*new_file_img(char *path, t_vars *window);
void			put_pixel_img(t_img *img, int x, int y, int color);
void			put_img_to_img(t_img *dst, t_img *src, int x, int y);
unsigned int	get_pixel_img(t_img *img, int x, int y);
void			fill_screen(t_img *img, int color);

// ... mlx free ...
void			destroy_list(void);
void			destroy_image(void *img);

// ... mlx events ...

int				move_up(t_vars *vars);
int				move_down(t_vars *vars);
int				move_right(t_vars *vars);
int				move_left(t_vars *vars);
int				render(t_vars *vars);

void			print_arr(char **lines);
#endif