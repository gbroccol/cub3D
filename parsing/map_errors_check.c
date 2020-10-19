/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:32:13 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:32:15 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		wrong_smb(t_data_map *all)
{
	int			i;
	int			j;

	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '0' || all->map[i][j] == '1' ||
				all->map[i][j] == '2' || all->map[i][j] == ' ' ||
				all->map[i][j] == 'N' || all->map[i][j] == 'E' ||
				all->map[i][j] == 'S' || all->map[i][j] == 'W')
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (1);
}

static int		point_of_view(t_data_map *all, char smb)
{
	if (smb == 'N')
		all->ray_cast->pov = M_PI / 2 * 3;
	else if (smb == 'E')
		all->ray_cast->pov = 0;
	else if (smb == 'S')
		all->ray_cast->pov = M_PI / 2;
	else if (smb == 'W')
		all->ray_cast->pov = M_PI;
	return (1);
}

static int		start_position(t_data_map *all)
{
	int			position;
	int			i;
	int			j;

	position = 0;
	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'N' || all->map[i][j] == 'E' ||
					all->map[i][j] == 'S' || all->map[i][j] == 'W')
				position = position + point_of_view(all, all->map[i][j]);
			j++;
		}
		i++;
	}
	if (position == 1)
		return (1);
	return (-1);
}

int				map_errors_check(t_data_map *all, t_map_er *mr)
{
	if (wrong_smb(all) == -1)
		return (errors_notify(0));
	else if (start_position(all) == -1)
		return (errors_notify(8));
	else if (map_walls_check(all, mr) == -1)
		return (errors_notify(9));
	else if (rewrite_map(all) == -1)
		return (-1);
	if (all->win_h > all->win_h_max)
		all->win_h = all->win_h_max;
	if (all->win_w > all->win_w_max)
		all->win_w = all->win_w_max;
	if (all->win_h < 192)
		all->win_h = 192;
	if (all->win_w < 320)
		all->win_w = 320;
	return (0);
}
