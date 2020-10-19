/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:40:13 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/04 19:40:15 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			check_wall(t_data_map *all, int grid_x, int grid_y)
{
	if (grid_x >= 0 && grid_x <= (all->map_w - 1)
			&& grid_y >= 0 && grid_y <= (all->map_h - 1))
	{
		if (all->map[grid_y][grid_x] == '2')
			if (all->spr_map[grid_y][grid_x] == '0')
				get_sprite(all, find_sprite(all->sprites, grid_y, grid_x));
		if (all->map[grid_y][grid_x] != '1')
			return (1);
	}
	return (0);
}

void		put_right_value(t_data_map *all, t_ray_cast *rc, char side)
{
	if (side == 'h')
	{
		rc->ray_distance = rc->h_dis;
		rc->grid_y = rc->hy / all->bl_h;
		if (all->py < rc->hy)
			rc->wall_site = 'S';
		else
			rc->wall_site = 'N';
		rc->x_tex = (float)((int)(rc->hx) % (int)all->bl_w);
	}
	else if (side == 'v')
	{
		rc->ray_distance = rc->v_dis;
		rc->grid_x = rc->vx / all->bl_w;
		if (all->px < rc->vx)
			rc->wall_site = 'E';
		else
			rc->wall_site = 'W';
		rc->x_tex = (float)((int)rc->vy % (int)all->bl_h);
	}
}

void		check_hor_inters(t_data_map *all, t_ray_cast *rc)
{
	if (0 < rc->angle && rc->angle < M_PI)
		rc->hy = (int)(all->py / all->bl_h) * (all->bl_h) + all->bl_h;
	else
		rc->hy = (int)(all->py / all->bl_h) * (all->bl_h) - 0.001;
	rc->hx = all->px + (all->py - rc->hy) / tan(rc->angle) * (-1);
	if (check_wall(all, rc->hx / all->bl_w, rc->hy / all->bl_h))
	{
		if (rc->angle > 0 && rc->angle < M_PI)
			rc->offset_y = all->bl_h;
		else
			rc->offset_y = all->bl_h * (-1);
		if (rc->angle > 0 && rc->angle < M_PI)
			rc->offset_x = all->bl_h / tan(rc->angle);
		else
			rc->offset_x = all->bl_h / tan(rc->angle) * (-1);
		while (check_wall(all, rc->hx / all->bl_w, rc->hy / all->bl_h))
		{
			rc->hx += rc->offset_x;
			rc->hy += rc->offset_y;
		}
		rc->h_dis = sqrt(pow(all->px - rc->hx, 2) + pow(all->py - rc->hy, 2));
	}
	else
		rc->h_dis = sqrt(pow(all->px - rc->hx, 2) + pow(all->py - rc->hy, 2));
}

void		check_vert_inters(t_data_map *all, t_ray_cast *rc)
{
	if ((rc->angle >= 0 && rc->angle <= M_PI / 2)
			|| (rc->angle >= 3 * M_PI / 2 && rc->angle <= 2 * M_PI))
		rc->vx = (int)(all->px / all->bl_w) * (all->bl_w) + all->bl_w;
	else
		rc->vx = (int)(all->px / all->bl_w) * (all->bl_w) - 0.001;
	rc->vy = all->py + (all->px - rc->vx) * tan(rc->angle) * (-1);
	if (check_wall(all, rc->vx / all->bl_w, rc->vy / all->bl_h))
	{
		if (M_PI / 2 < rc->angle && rc->angle < 3 * M_PI / 2)
			rc->offset_y = all->bl_w * tan(rc->angle) * (-1);
		else
			rc->offset_y = all->bl_w * tan(rc->angle);
		if (rc->angle <= M_PI / 2 || rc->angle >= 3 * M_PI / 2)
			rc->offset_x = all->bl_w;
		else
			rc->offset_x = all->bl_w * (-1);
		while (check_wall(all, rc->vx / all->bl_w, rc->vy / all->bl_h))
		{
			rc->vy += rc->offset_y;
			rc->vx += rc->offset_x;
		}
		rc->v_dis = sqrt(pow(all->px - rc->vx, 2) + pow(all->py - rc->vy, 2));
	}
	else
		rc->v_dis = sqrt(pow(all->px - rc->vx, 2) + pow(all->py - rc->vy, 2));
}

void		ray_casting(t_data_map *all, t_ray_cast *rc)
{
	rc->col = 0;
	while (rc->col < all->win_w)
	{
		rc->angle = rc->pov - rc->fov / 2 + rc->fov / all->win_w * rc->col;
		while (rc->angle > 2 * M_PI)
			rc->angle -= 2 * M_PI;
		while (rc->angle < 0)
			rc->angle += 2 * M_PI;
		check_hor_inters(all, all->ray_cast);
		check_vert_inters(all, all->ray_cast);
		if (rc->v_dis < rc->h_dis)
			put_right_value(all, rc, 'v');
		else if (rc->v_dis > rc->h_dis)
			put_right_value(all, rc, 'h');
		else
		{
			if (rc->wall_site == 'N' || rc->wall_site == 'S')
				put_right_value(all, rc, 'h');
			else
				put_right_value(all, rc, 'v');
		}
		all->ray_cast->dist_to_walls[rc->col] = rc->ray_distance;
		draw_column(all, all->ray_cast, rc->col);
		rc->col++;
	}
}
