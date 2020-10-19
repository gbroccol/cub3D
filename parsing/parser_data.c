/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:33:12 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/08 18:48:15 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*ft_strdup_texture(const char *str)
{
	char	*res;
	int		i;
	int		len;
	int		spaces;

	len = ft_strlen((char *)str);
	len--;
	while (str[len] == ' ')
		len--;
	spaces = ft_strlen((char *)str) - len - 1;
	len = ft_strlen((char *)str);
	if ((res = malloc(len - spaces + 1)) == NULL)
		return (NULL);
	i = 0;
	while (len - spaces)
	{
		res[i] = str[i];
		i++;
		len--;
	}
	res[i] = '\0';
	return (res);
}

static int	texture(t_data_map *all, char *str, char type, t_map_er *mr)
{
	str++;
	str++;
	while (*str == ' ')
		str++;
	if (type == 'N')
		all->path_no = ft_strdup_texture(str);
	else if (type == 'S')
		all->path_so = ft_strdup_texture(str);
	else if (type == 'W')
		all->path_we = ft_strdup_texture(str);
	else if (type == 'E')
		all->path_ea = ft_strdup_texture(str);
	else if (type == 'P')
		all->path_sprite = ft_strdup_texture(str);
	if (type == 'N')
		mr->no++;
	else if (type == 'S')
		mr->so++;
	else if (type == 'W')
		mr->we++;
	else if (type == 'E')
		mr->ea++;
	else if (type == 'P')
		mr->spr++;
	return (0);
}

static int	flr_ceil2(t_data_map *all, char *str, char type, t_map_er *m_r)
{
	while (*str == ' ')
		str++;
	if (*str != '\0')
		return (errors_notify(2));
	if (m_r->r < 0 || m_r->r > 255 || m_r->g < 0
			|| m_r->g > 255 || m_r->b < 0 || m_r->b > 255)
		return (errors_notify(2));
	if (type == 'F')
	{
		all->floor_hex = (1 << 24 | m_r->r << 16 | m_r->g << 8 | m_r->b);
		m_r->floor_color_er++;
	}
	else
	{
		all->ceiling_hex = (1 << 24 | m_r->r << 16 | m_r->g << 8 | m_r->b);
		m_r->ceiling_color_er++;
	}
	return (0);
}

static int	flr_ceil(t_data_map *all, char *str, char type, t_map_er *mr)
{
	str++;
	while (all->tmp_h <= 2)
	{
		while (*str == ' ')
			str++;
		if (*str < '0' || *str > '9')
			return (errors_notify(2));
		if (all->tmp_h == 0)
			mr->r = ft_atoi(str);
		else if (all->tmp_h == 1)
			mr->g = ft_atoi(str);
		else if (all->tmp_h == 2)
			mr->b = ft_atoi(str);
		while (*str >= '0' && *str <= '9')
			str++;
		while (*str == ' ')
			str++;
		if (*str != ',' && (all->tmp_h == 0 || all->tmp_h == 1))
			return (errors_notify(2));
		if (all->tmp_h != 2)
			str++;
		all->tmp_h++;
	}
	return (flr_ceil2(all, str, type, mr));
}

int			parser_data(t_data_map *all, char *str, t_map_er *mr)
{
	all->tmp_h = 0;
	if (str[0] == '\0')
		return (0);
	else if (str[0] == 'R')
		return (resolution(all, str, mr));
	else if (str[0] == 'N' && str[1] == 'O')
		return (texture(all, str, 'S', mr));
	else if (str[0] == 'S' && str[1] == 'O')
		return (texture(all, str, 'N', mr));
	else if (str[0] == 'W' && str[1] == 'E')
		return (texture(all, str, 'E', mr));
	else if (str[0] == 'E' && str[1] == 'A')
		return (texture(all, str, 'W', mr));
	else if (str[0] == 'S' && str[1] == ' ')
		return (texture(all, str, 'P', mr));
	else if (str[0] == 'F' && str[1] == ' ')
		return (flr_ceil(all, str, 'F', mr));
	else if (str[0] == 'C' && str[1] == ' ')
		return (flr_ceil(all, str, 'C', mr));
	else if (str[0] != ' ' && str[0] != '\0' && str[0] != '1' && str[0] != '0')
		return (errors_notify(11));
	else if (str[0] == ' ' || str[0] == '1' || str[0] == '0')
		return (1);
	return (0);
}
