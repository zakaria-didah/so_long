/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:49:36 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/22 21:26:50 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_list	**get_head_list(void)
{
	static t_list	*head;

	if (!head)
		head = ft_calloc(sizeof(t_list), 1);
	return (&head);
}

void	destroy_list(void)
{
	t_list	*head;
	t_vars	*vars;

	head = *get_head_list();
	vars = *get_vars();
	ft_lstiter(head, destroy_image);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

int	random_int(int min, int max)
{
	int	x;

	x = rand() % (max - min + 1) + min;
	return (x);
}

void	fill_screen(t_img *img, int color)
{
	int		i;
	int		j;
	t_vars	*vars;

	i = 0;
	j = 0;
	vars = *get_vars();
	while (i < vars->width)
	{
		while (j < vars->hight)
		{
			put_pixel_img(img, i, j, color);
			j++;
		}
		i++;
		j = 0;
	}
}

int	_close(void)
{
	destroy_list();
	return (free_garb(), exit(0), 0);
}
