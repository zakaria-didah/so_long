/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_things.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:42:47 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 19:42:28 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_img_to_img(t_img *dst, t_img *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src->w)
	{
		j = 0;
		while (j < src->h)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

t_img	*new_file_img(char *path, t_vars *window)
{
	t_img	*image;

	image = ft_calloc(sizeof(t_img), 1);
	image->img_ptr = mlx_xpm_file_to_image(window->mlx, path, &image->w,
			&image->h);
	ft_lstadd_back(get_head_list(), ft_lstnew(image->img_ptr));
	if (!image->img_ptr)
	{
		ft_printf_fd(2, "Error\nFile [%s] could not be read\n", path);
		return (destroy_list(), free_garb(), exit(1), NULL);
	}
	else
	{
		image->addr = mlx_get_data_addr(image->img_ptr, &(image->bpp),
				&(image->line_len), &(image->endian));
		if (!image->addr)
		{
			ft_printf_fd(2, "Error\nAn error occurred with the file [%s]\n",
				path);
			return (destroy_list(), free_garb(), exit(1), NULL);
		}
	}
	return (image);
}

t_img	*new_img(int w, int h, t_vars *window)
{
	t_img	*image;

	image = ft_calloc(sizeof(t_img), 1);
	image->img_ptr = mlx_new_image(window->mlx, w, h);
	ft_lstadd_back(get_head_list(), ft_lstnew(image->img_ptr));
	image->addr = mlx_get_data_addr(image->img_ptr, &(image->bpp),
			&(image->line_len), &(image->endian));
	image->w = w;
	image->h = h;
	return (image);
}

t_img	*dup_img(t_img *img)
{
	t_img	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = new_img(img->w, img->h, (*get_vars()));
	while (i < img->w)
	{
		while (j < img->h)
		{
			put_pixel_img(tmp, i, j, get_pixel_img(img, i, j));
			j++;
		}
		i++;
		j = 0;
	}
	return (tmp);
}

t_img	*merge_img(t_img *dst)
{
	t_img	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = dup_img((*get_vars())->map->ground);
	while (i < dst->w)
	{
		while (j < dst->h)
		{
			put_pixel_img(tmp, i, j, get_pixel_img(dst, i, j));
			j++;
		}
		i++;
		j = 0;
	}
	return (tmp);
}
