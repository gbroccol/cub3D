/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:59:10 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/07 16:18:26 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		free_textures(t_data_map *all, int i)
{
	if (i > 0)
		free(all->img);
	if (i > 1)
		free(all->t_no);
	if (i > 2)
		free(all->t_so);
	if (i > 3)
		free(all->t_we);
	if (i > 4)
		free(all->t_ea);
	if (i > 5)
		free(all->t_spr);
	return (-1);
}

int		malloc_textures(t_data_map *all)
{
	if (!(all->img = malloc_img_list()))
		return (free_textures(all, 0));
	if (!(all->t_no = malloc_img_list()))
		return (free_textures(all, 1));
	if (!(all->t_so = malloc_img_list()))
		return (free_textures(all, 2));
	if (!(all->t_we = malloc_img_list()))
		return (free_textures(all, 3));
	if (!(all->t_ea = malloc_img_list()))
		return (free_textures(all, 4));
	if (!(all->t_spr = malloc_img_list()))
		return (free_textures(all, 5));
	return (0);
}
