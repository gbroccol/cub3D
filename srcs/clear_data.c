/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:08:12 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:29:44 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void			ray_cast_clear(t_ray_cast *rc)
{
	rc->fov = M_PI / 3;
	rc->pov = M_PI;
	rc->angle = 0.0;
	rc->dist_to_pp = 0.0;
	rc->h_dis = 0.0;
	rc->v_dis = 0.0;
	rc->offset_y = 0.0;
	rc->offset_x = 0.0;
	rc->hx = 0.0;
	rc->hy = 0.0;
	rc->vx = 0.0;
	rc->vy = 0.0;
	rc->grid_x = 0;
	rc->grid_y = 0;
	rc->x_tex = 0.0;
	rc->y_tex = 0.0;
	rc->wall_site = 'N';
	rc->wall_str = 0;
	rc->color = 0;
	rc->wall_size = 0;
	rc->ray_distance = 0.0;
	rc->dist_to_walls = NULL;
	rc->spr_x = 0;
	rc->spr_y = 0;
	rc->spr_dist = 0.0;
}

static int			clear_data2(t_data_map *all)
{
	all->map_w = 0;
	all->map_h = 0;
	all->spr_map = NULL;
	all->flag = 0;
	if (!(all->ray_cast = malloc(sizeof(t_ray_cast))))
		return (-1);
	ray_cast_clear(all->ray_cast);
	all->ray_cast->col = 0;
	all->sprites = NULL;
	return (0);
}

int					clear_data(t_data_map *all)
{
	all->mlx = mlx_init();
	all->mlx_win = NULL;
	all->map = NULL;
	all->bl_w = 0.0;
	all->bl_h = 0.0;
	all->tmp_h = 0;
	all->tmp_w = 0;
	all->make_scr = 0;
	all->px = 0;
	all->py = 0;
	all->win_w = 0;
	all->win_h = 0;
	all->win_w_max = 0;
	all->win_h_max = 0;
	all->path_no = NULL;
	all->path_so = NULL;
	all->path_we = NULL;
	all->path_ea = NULL;
	all->path_sprite = NULL;
	all->floor_hex = 0;
	all->ceiling_hex = 0;
	return (clear_data2(all));
}
