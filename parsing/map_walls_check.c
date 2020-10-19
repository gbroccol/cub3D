/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:34:09 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 19:34:15 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		map_stop(t_data_map *all, int i)
{
	while (all->map[i])
	{
		if (all->map[i][0] != '\0')
			return (-1);
		i++;
	}
	return (0);
}

static int		check_around(int i, int j, t_data_map *all)
{
	if (j == 0 || (j + 1) == ft_strlen(all->map[i]))
		return (-1);
	else if (all->map[i][j - 1] == ' ' || all->map[i][j + 1] == ' '
			|| all->map[i][j + 1] == '\0' || all->map[i][j + 1] == ' ')
		return (-1);
	else if (ft_strlen(all->map[i - 1]) <= j)
		return (-1);
	else if (ft_strlen(all->map[i + 1]) <= j)
		return (-1);
	else if (all->map[i - 1][j] == ' ' || all->map[i + 1][j] == ' ')
		return (-1);
	return (0);
}

static int		check_middel(t_data_map *all, int len)
{
	int			i;
	int			j;

	i = 1;
	while (all->map[i] && i <= len)
	{
		if (all->map[i][0] == '\0')
			return (map_stop(all, i));
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '0' || all->map[i][j] == '2'
				|| all->map[i][j] == 'S' || all->map[i][j] == 'N'
				|| all->map[i][j] == 'E' || all->map[i][j] == 'W')
			{
				if (check_around(i, j, all) == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int				map_walls_check(t_data_map *all, t_map_er *mr)
{
	int			i;

	i = 0;
	while (all->map[0][i])
	{
		if (all->map[0][i] != '1' && all->map[0][i] != ' ')
			return (-1);
		i++;
	}
	if (mr->map_len <= 1 || ((mr->map_len + 1) > 2
			&& check_middel(all, (mr->map_len - 1)) == -1))
		return (-1);
	i = 0;
	if (mr->map_len != 0)
		while (all->map[mr->map_len][i])
		{
			if (all->map[mr->map_len][i] != '1'
				&& all->map[mr->map_len][i] != ' ')
				return (-1);
			i++;
		}
	return (1);
}
