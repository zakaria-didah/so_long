/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:07:10 by zdidah            #+#    #+#             */
/*   Updated: 2025/02/12 18:08:17 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char *), ft_arrlen(arr) + 1);
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	return (new);
}
