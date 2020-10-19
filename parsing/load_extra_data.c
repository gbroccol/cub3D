/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_extra_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:31:56 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:31:57 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		ft_lstadd_back_spr(t_sprite **lst, t_sprite *new)
{
	t_sprite	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int		create_sprite_list(t_data_map *all)
{
	int			i;
	int			j;
	t_sprite	*new;

	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '2')
			{
				if ((new = malloc(sizeof(t_sprite))) == NULL)
					return (-1);
				new->visible = 0;
				new->x_2d = j;
				new->y_2d = i;
				new->next = NULL;
				ft_lstadd_back_spr(&(all->sprites), new);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void		player_position(t_data_map *all)
{
	int			i;
	int			j;

	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'N' || all->map[i][j] == 'W'
					|| all->map[i][j] == 'S' || all->map[i][j] == 'E')
			{
				all->px = j * all->bl_w + all->bl_w / 2;
				all->py = i * all->bl_h + all->bl_h / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}

int				load_extra_data(t_data_map *all, t_ray_cast *rc)
{
	if (!(rc->dist_to_walls = malloc((all->win_w + 1) * sizeof(float))))
		return (-1);
	rc->dist_to_walls[all->win_w] = '\0';
	if (load_textures(all) == -1 || create_sprite_map(all) == -1)
	{
		free(all->ray_cast->dist_to_walls);
		return (-1);
	}
	rc->dist_to_pp = (all->win_w / 2) / tan(M_PI / 6);
	all->bl_w = 64;
	all->bl_h = 64;
	player_position(all);
	if (create_sprite_list(all) == -1)
	{
		free(all->ray_cast->dist_to_walls);
		return (-1);
	}
	return (0);
}
