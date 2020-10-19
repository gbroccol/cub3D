/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:33:23 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:33:25 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				ft_atoi_max(const char *str, long long max)
{
	int			i;
	long long	res;
	int			minus;

	i = 0;
	res = 0;
	minus = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > ((res * 10) + (str[i] - '0')) && minus == 1)
			return (0);
		else if (res > ((res * 10) + (str[i] - '0')) && minus == 0)
			return (-1);
		else
			res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res > max ? max : res);
}

int				resolution(t_data_map *all, char *str, t_map_er *mr)
{
	mlx_get_screen_size(&all->mlx, &all->win_w_max, &all->win_h_max);
	str++;
	while (*str == ' ')
		str++;
	if (*str < '0' || *str > '9')
		return (errors_notify(10));
	all->win_w = ft_atoi_max(str, all->win_w_max);
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ')
		str++;
	if (*str < '0' || *str > '9')
		return (errors_notify(10));
	all->win_h = ft_atoi_max(str, all->win_h_max);
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ')
		str++;
	if (*str != '\0' || all->win_h <= 0 || all->win_w <= 0)
		return (errors_notify(10));
	mr->width++;
	mr->height++;
	return (0);
}
