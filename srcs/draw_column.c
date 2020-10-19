/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:31:42 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/04 17:33:14 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			pixel_put(t_img *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int				get_clr(t_img *text, int x, int y, float line)
{
	int			index;
	int			*dst;

	y = y * text->height / line;
	index = (x + y * text->width);
	dst = text->addr_tex + index;
	return (*(unsigned int*)dst);
}

static int		draw_wall(int x, int y_start, t_ray_cast *rc, t_data_map *all)
{
	while (y_start < ((rc->wall_str) + rc->wall_size) && y_start < all->win_h)
	{
		if (rc->wall_site == 'N')
			rc->color = get_clr(all->t_no, rc->x_tex, rc->y_tex, rc->wall_size);
		else if (rc->wall_site == 'S')
			rc->color = get_clr(all->t_so, rc->x_tex, rc->y_tex, rc->wall_size);
		else if (rc->wall_site == 'W')
			rc->color = get_clr(all->t_we, rc->x_tex, rc->y_tex, rc->wall_size);
		else if (rc->wall_site == 'E')
			rc->color = get_clr(all->t_ea, rc->x_tex, rc->y_tex, rc->wall_size);
		pixel_put(all->img, x, y_start, rc->color);
		y_start++;
		rc->y_tex++;
	}
	return (y_start);
}

void			draw_column(t_data_map *all, t_ray_cast *rc, int x)
{
	int			y_start;

	y_start = 0;
	rc->y_tex = 0;
	rc->ray_distance *= cos(all->ray_cast->pov - all->ray_cast->angle);
	rc->wall_size = (all->bl_w * rc->dist_to_pp) / rc->ray_distance;
	rc->wall_str = (all->win_h / 2) - (rc->wall_size / 2);
	while (y_start < rc->wall_str)
		pixel_put(all->img, x, y_start++, all->ceiling_hex);
	if (rc->wall_size > all->win_h)
		rc->y_tex = (rc->wall_size - all->win_h) / 2;
	y_start = draw_wall(x, y_start, rc, all);
	while (y_start++ < all->win_h)
		pixel_put(all->img, x, y_start - 1, all->floor_hex);
}
