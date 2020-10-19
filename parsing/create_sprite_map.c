/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sprite_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:20:38 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/07 16:20:40 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		free_spr_map(int i, char **map)
{
	i--;
	while (i >= 0)
	{
		free(map[i]);
		i--;
	}
	free(map);
	return (-1);
}

int				create_sprite_map(t_data_map *all)
{
	int			i;
	int			j;

	i = 0;
	if (!(all->spr_map = (char **)malloc((all->map_h + 1) * sizeof(char **))))
		return (-1);
	while (i < all->map_h)
	{
		if (!(all->spr_map[i] = malloc((all->map_w + 1) * sizeof(char *))))
			return (free_spr_map(i, all->spr_map));
		j = 0;
		while (j < all->map_w)
		{
			all->spr_map[i][j] = '0';
			j++;
		}
		all->spr_map[i][all->map_w] = '\0';
		i++;
	}
	all->spr_map[i] = NULL;
	return (0);
}
