/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:21:15 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/04 19:21:22 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			key_press_exit(t_data_map *all)
{
	mlx_destroy_image(all->mlx, all->img->img);
	if (all->mlx && all->mlx_win)
		mlx_destroy_window(all->mlx, all->mlx_win);
	exit(0);
}

static int	check_moving2(t_data_map *all, char side)
{
	if (side == 'l')
	{
		all->tmp_h = all->py - sin(all->ray_cast->pov + (M_PI / 2)) * 20;
		all->tmp_w = all->px - cos(all->ray_cast->pov + (M_PI / 2)) * 20;
	}
	else if (side == 'r')
	{
		all->tmp_h = all->py + sin(all->ray_cast->pov + (M_PI / 2)) * 20;
		all->tmp_w = all->px + cos(all->ray_cast->pov + (M_PI / 2)) * 20;
	}
	all->tmp_h = (all->tmp_h / 64);
	all->tmp_w = (all->tmp_w / 64);
	if (all->tmp_h >= (all->map_h - 1) || all->tmp_w >= (all->map_w - 1)
		|| all->tmp_h < 1 || all->tmp_w < 1
		|| all->map[all->tmp_h][all->tmp_w] == '1'
		|| all->map[all->tmp_h][all->tmp_w] == ' ')
		return (0);
	return (1);
}

static int	check_moving(t_data_map *all, char side)
{
	if (side == 'u')
	{
		all->tmp_h = all->py + sin(all->ray_cast->pov) * 70;
		all->tmp_w = all->px + cos(all->ray_cast->pov) * 70;
	}
	else if (side == 'd')
	{
		all->tmp_h = all->py - sin(all->ray_cast->pov) * 20;
		all->tmp_w = all->px - cos(all->ray_cast->pov) * 20;
	}
	all->tmp_h = (all->tmp_h / 64);
	all->tmp_w = (all->tmp_w / 64);
	if (all->tmp_h >= (all->map_h - 1) || all->tmp_w >= (all->map_w - 1)
		|| all->tmp_h < 1 || all->tmp_w < 1
		|| all->map[all->tmp_h][all->tmp_w] == '1'
		|| all->map[all->tmp_h][all->tmp_w] == ' ')
		return (0);
	return (1);
}

void		key_press2(int key, t_data_map *all)
{
	if ((key == 13 || key == 119 || key == 126) && check_moving(all, 'u'))
	{
		all->py += sin(all->ray_cast->pov) * 20;
		all->px += cos(all->ray_cast->pov) * 20;
	}
	else if ((key == 1 || key == 115 || key == 125) && check_moving(all, 'd'))
	{
		all->py -= sin(all->ray_cast->pov) * 20;
		all->px -= cos(all->ray_cast->pov) * 20;
	}
	else if ((key == 0 || key == 97) && check_moving2(all, 'l'))
	{
		all->py -= sin(all->ray_cast->pov + (M_PI / 2)) * 10;
		all->px -= cos(all->ray_cast->pov + (M_PI / 2)) * 10;
	}
	else if ((key == 2 || key == 100) && check_moving2(all, 'r'))
	{
		all->py += sin(all->ray_cast->pov + (M_PI / 2)) * 10;
		all->px += cos(all->ray_cast->pov + (M_PI / 2)) * 10;
	}
}

int			key_press(int key, t_data_map *all)
{
	if (key != 123 && key != 124 && key != 53)
		key_press2(key, all);
	else if (key == 53)
		key_press_exit(all);
	else if (key == 123)
		all->ray_cast->pov -= 0.1;
	else if (key == 124)
		all->ray_cast->pov += 0.1;
	mlx_destroy_image(all->mlx, all->img->img);
	draw_screen(all);
	return (0);
}
