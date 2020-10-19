/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:46:33 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/06 17:46:42 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void			clear_sprite_map(t_data_map *all)
{
	int				i;
	int				j;

	i = 0;
	while (all->spr_map[i])
	{
		j = 0;
		while (all->spr_map[i][j])
		{
			all->spr_map[i][j] = '0';
			j++;
		}
		i++;
	}
}

static void			draw_sprites(t_data_map *all, t_sprite *spr)
{
	int				i;
	int				j;
	int				color;

	i = 0;
	color = 0;
	while (++i < spr->size)
	{
		if ((spr->h_of + i) < 0 || spr->h_of + i >= all->win_w)
			continue;
		if (all->ray_cast->dist_to_walls[spr->h_of + i] < spr->dist)
			continue;
		j = 0;
		while (++j < spr->size)
		{
			if (spr->v_of + j < 0 || spr->v_of + j >= all->win_h)
				continue;
			color = get_clr(all->t_spr, ((int)(i * 64 / spr->size)),
					((int)(j / 2)), ((float)(spr->size / 2)));
			if (color != 0)
            {
                if ((spr->v_of + j + 10) >= all->win_h)
                    continue;
                else
                    pixel_put(all->img, spr->h_of + i, spr->v_of + j + 10, color);
            }
		}
	}
	spr->visible = 0;
}

static void			change_value(t_data_map *all, t_sprite *result)
{
	if (all->ray_cast->spr_dist < result->dist)
	{
		all->ray_cast->spr_dist = result->dist;
		all->ray_cast->spr_x = result->x_2d;
		all->ray_cast->spr_y = result->y_2d;
	}
}

void				spr_handle(t_data_map *all, t_sprite *lst, t_ray_cast *rc)
{
	t_sprite	*result;

	if (lst == NULL)
		return ;
	result = lst;
	while (1)
	{
		while (1)
		{
			if (result->visible == 1)
				change_value(all, result);
			if (result->next == NULL)
				break ;
			result = result->next;
		}
		if (rc->spr_dist != 0)
		{
			draw_sprites(all, find_sprite(all->sprites, rc->spr_y, rc->spr_x));
			result = lst;
			rc->spr_dist = 0.0;
		}
		else
			break ;
	}
	clear_sprite_map(all);
}
