/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:32:53 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:32:55 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_map_er	*mr_clear(void)
{
	t_map_er	*mr;

	if (!(mr = malloc(sizeof(t_map_er))))
		return (NULL);
	mr->status = 1;
	mr->str = NULL;
	mr->map_str = 0;
	mr->width = 0;
	mr->height = 0;
	mr->no = 0;
	mr->so = 0;
	mr->we = 0;
	mr->ea = 0;
	mr->spr = 0;
	mr->floor_color_er = 0;
	mr->ceiling_color_er = 0;
	mr->r = 0;
	mr->g = 0;
	mr->b = 0;
	mr->map_len = -1;
	return (mr);
}

static int		parsing(t_data_map *all, int open_return)
{
	while (all->mr->status > 0 && all->mr->map_str == 0)
	{
		all->mr->status = get_next_line(open_return, &all->mr->str);
		if ((all->mr->map_str = parser_data(all, all->mr->str, all->mr)) == -1)
		{
			free(all->mr);
			return (-1);
		}
		if (all->mr->map_str == 1)
		{
			parser_map(all, all->mr->str, all->mr);
			while (all->mr->status > 0 && all->mr->map_str == 1)
			{
				free(all->mr->str);
				all->mr->status = get_next_line(open_return, &all->mr->str);
				all->mr->map_str = parser_map(all, all->mr->str, all->mr);
			}
		}
		free(all->mr->str);
	}
	return (0);
}

int				mr(t_data_map *all, char *file)
{
	int			open_return;

	if ((open_return = open(file, O_RDONLY)) == -1)
		return (errors_notify(1));
	if (!(all->mr = mr_clear()))
		return (-1);
	if (parsing(all, open_return) == -1)
		return (-1);
	if (check_all_errors(all, all->mr) == -1)
		return (-1);
	return (0);
}
