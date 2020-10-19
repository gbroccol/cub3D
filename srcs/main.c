/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:30:24 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:30:25 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int					draw_screen(t_data_map *all)
{
	all->img->img = mlx_new_image(all->mlx, all->win_w, all->win_h);
	all->img->addr = mlx_get_data_addr(all->img->img,
			&all->img->bpp, &all->img->len, &all->img->end);
	ray_casting(all, all->ray_cast);
	spr_handle(all, all->sprites, all->ray_cast);
	if (all->argc == 2)
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
	return (0);
}

static int			pre_drawing(int argc, char **argv, t_data_map *all)
{
	ft_bzero(all, sizeof(t_data_map));
	all->argc = argc;
	if ((check_argc_argv(argc, argv) == -1))
		return (-1);
	if (clear_data(all) == -1)
		return (-1);
	if (mr(all, argv[1]) == -1)
	{
		free(all->ray_cast);
		return (-1);
	}
	if (load_extra_data(all, all->ray_cast) == -1)
	{
		free(all->map);
		free(all->path_no);
		free(all->path_so);
		free(all->path_we);
		free(all->path_ea);
		free(all->path_sprite);
		free(all->mr);
		free(all->ray_cast);
		return (-1);
	}
	return (0);
}

int					main(int argc, char **argv)
{
	t_data_map		all;

	if (pre_drawing(argc, argv, &all) == -1)
		return (-1);
	if (argc == 2)
		all.mlx_win = mlx_new_window(all.mlx, all.win_w, all.win_h, "gbroccol");
	if (argc == 2 && all.mlx_win == NULL)
		return (free_all(&all));
	all.argc = argc;
	draw_screen(&all);
	if (argc == 3)
	{
		if (make_screen(&all) == -1)
			return (free_all(&all));
	}
	else
	{
		mlx_hook(all.mlx_win, 2, (1L << 0), key_press, &all);
		mlx_hook(all.mlx_win, 17, 0, key_press_exit, &all);
		mlx_loop(all.mlx);
	}
	free_all(&all);
	return (0);
}
