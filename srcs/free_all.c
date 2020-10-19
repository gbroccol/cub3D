/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:49:35 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/07 16:49:37 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		free_sprite_list(t_sprite *sprites)
{
	t_sprite	*tmp;

	if (!sprites)
		return ;
	while (sprites)
	{
		tmp = sprites->next;
		free(sprites);
		sprites = NULL;
		sprites = tmp;
	}
}

int				free_all(t_data_map *all)
{
	free(all->spr_map);
	free_textures(all, 6);
	free(all->ray_cast->dist_to_walls);
	free(all->map);
	free(all->path_no);
	free(all->path_so);
	free(all->path_we);
	free(all->path_ea);
	free(all->path_sprite);
	free(all->mr);
	free(all->ray_cast);
	free_sprite_list(all->sprites);
	exit(0);
	return (-1);
}
