/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors_check2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:32:36 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 18:32:37 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char		*ft_strdup_plus(const char *s, int full_len)
{
	char		*res;
	int			i;
	int			len;

	len = ft_strlen((char *)s);
	if ((res = malloc(full_len + 1)) == NULL)
		return (NULL);
	i = 0;
	while (len)
	{
		if (s[i] == ' ' || s[i] == '\0')
			res[i] = '1';
		else
			res[i] = s[i];
		i++;
		len--;
	}
	len = ft_strlen((char *)s);
	while (full_len-- != len)
		res[i++] = '1';
	res[i] = '\0';
	return (res);
}

int				rewrite_map(t_data_map *all)
{
	char		**new_ar;
	int			i;

	if (!(new_ar = malloc((all->map_h + 1) * sizeof(char *))))
		return (-1);
	i = 0;
	while (i < all->map_h)
	{
		if ((new_ar[i] = ft_strdup_plus(all->map[i], all->map_w)) == NULL)
			return (-1);
		i++;
	}
	new_ar[i] = NULL;
	i = 0;
	while (i < all->map_h)
	{
		free(all->map[i]);
		i++;
	}
	free(all->map);
	all->map = new_ar;
	return (0);
}
