/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:30:04 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:30:06 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_sprite		*find_sprite(t_sprite *lst, int y, int x)
{
	t_sprite	*result;

	if (lst == NULL)
		return (0);
	result = lst;
	while (result->y_2d != y && result->next)
		result = result->next;
	while (result->x_2d != x && result->next)
		result = result->next;
	return (result);
}

void			get_sprite(t_data_map *all, t_sprite *sprite)
{
	all->spr_map[sprite->y_2d][sprite->x_2d] = '1';
	sprite->visible = 1;
	sprite->x_3d = sprite->x_2d * all->bl_w + (all->bl_w / 2);
	sprite->y_3d = sprite->y_2d * all->bl_h + (all->bl_h / 2);
	sprite->dir = atan2(sprite->y_3d - all->py, sprite->x_3d - all->px);
	while (sprite->dir - all->ray_cast->pov > M_PI)
		sprite->dir -= 2 * M_PI;
	while (sprite->dir - all->ray_cast->pov < -M_PI)
		sprite->dir += 2 * M_PI;
	sprite->dist = sqrt(pow(all->px - sprite->x_3d, 2) +
		pow(all->py - sprite->y_3d, 2));
	sprite->size = (all->bl_w * all->ray_cast->dist_to_pp / sprite->dist);
	sprite->h_of = (sprite->dir - all->ray_cast->pov) * (all->win_w /
		all->ray_cast->fov) + (all->win_w / 2) - (sprite->size / 2);
	sprite->v_of = (all->win_h / 2) - (sprite->size / 2);
}
