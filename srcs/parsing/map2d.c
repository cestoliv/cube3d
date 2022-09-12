/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:37:13 by ocartier          #+#    #+#             */
/*   Updated: 2022/09/12 10:37:19 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map2D	*dup_map2D(t_map2D *map2D)
{
	t_map2D	*dup;
	size_t	cur;

	dup = malloc(sizeof(t_map2D));
	dup->width = map2D->width;
	dup->height = map2D->height;
	dup->map = malloc(sizeof(char *) * (dup->height + 1));
	cur = 0;
	while (cur < dup->height)
	{
		dup->map[cur] = ft_strdup(map2D->map[cur]);
		cur++;
	}
	dup->map[cur] = NULL;
	return (dup);
}
