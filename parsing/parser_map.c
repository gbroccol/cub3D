/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:23:29 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/07 16:23:31 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		free_ex_map(t_data_map *all, int len)
{
	int			i;

	i = 0;
	while (i < len)
	{
		free(all->map[i]);
		i++;
	}
	free(all->map);
}

int				parser_map(t_data_map *all, char *str, t_map_er *mr)
{
	char		**new_ar;
	int			replace;

	if (str[0] != '\0' && str[0] != '1' && str[0] != '0' && str[0] != ' ')
		return (errors_notify(6));
	mr->map_len++;
	if (!(new_ar = (char **)malloc((mr->map_len + 2) * sizeof(char **))))
		return (-1);
	replace = 0;
	while (replace < mr->map_len)
	{
		new_ar[replace] = ft_strdup(all->map[replace]);
		replace++;
	}
	new_ar[replace] = ft_strdup(str);
	replace++;
	new_ar[replace] = NULL;
	all->map_h = replace;
	free_ex_map(all, mr->map_len);
	all->map = new_ar;
	if (all->map_w < ft_strlen(str))
		all->map_w = ft_strlen(str);
	return (1);
}
