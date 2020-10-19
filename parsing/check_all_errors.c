/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:27:38 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/07 16:28:42 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				data_errors_amount(t_map_er *mr)
{
	if (mr->width != 1)
		return (errors_notify(3));
	if (mr->height != 1)
		return (errors_notify(3));
	if (mr->no > 1 || mr->so > 1 || mr->we > 1 || mr->ea > 1 || mr->spr > 1)
		return (errors_notify(4));
	if (mr->no < 1 || mr->so < 1 || mr->we < 1 || mr->ea < 1 || mr->spr < 1)
		return (errors_notify(5));
	if (mr->floor_color_er != 1)
		return (errors_notify2(14));
	if (mr->ceiling_color_er != 1)
		return (errors_notify2(13));
	return (0);
}

int				textur_exist(t_data_map *all)
{
	int			fd;

	if ((fd = open(all->path_no, O_RDONLY)) == -1)
		return (errors_notify(7));
	close(fd);
	if ((fd = open(all->path_so, O_RDONLY)) == -1)
		return (errors_notify(7));
	close(fd);
	if ((fd = open(all->path_we, O_RDONLY)) == -1)
		return (errors_notify(7));
	close(fd);
	if ((fd = open(all->path_ea, O_RDONLY)) == -1)
		return (errors_notify(7));
	close(fd);
	if ((fd = open(all->path_sprite, O_RDONLY)) == -1)
		return (errors_notify(7));
	close(fd);
	return (0);
}

int				check_all_errors(t_data_map *all, t_map_er *mr)
{
	if (mr->status == 0 && mr->map_str == 0)
	{
		free(all->map);
		free(all->path_no);
		free(all->path_so);
		free(all->path_we);
		free(all->path_ea);
		free(all->mr);
		return (errors_notify2(12));
	}
	if (mr->map_str == -1 || map_errors_check(all, mr) == -1
		|| data_errors_amount(mr) == -1 || textur_exist(all) == -1)
	{
		free(all->map);
		free(all->path_no);
		free(all->path_so);
		free(all->path_we);
		free(all->path_ea);
		free(all->mr);
		return (-1);
	}
	return (0);
}
