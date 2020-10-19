/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:52:10 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/05 19:52:12 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			*load_text_img(t_data_map *all, char *path, t_img *texture)
{
	int			height;
	int			width;
	void		*img;

	height = 0;
	width = 0;
	img = NULL;
	img = mlx_xpm_file_to_image(all->mlx, path, &width, &height);
	texture->height = height;
	texture->width = width;
	return (img);
}

static char		*load_text_addr(t_img *text)
{
	char		*addr;
	int			bpp;
	int			len;
	int			end;

	addr = mlx_get_data_addr(text->img, &bpp, &len, &end);
	text->bpp = bpp;
	text->len = len;
	text->end = end;
	return (addr);
}

t_img			*malloc_img_list(void)
{
	t_img		*list;

	if (!(list = malloc(sizeof(t_img))))
		return (NULL);
	list->img = NULL;
	list->addr = NULL;
	list->addr_tex = NULL;
	list->bpp = 0;
	list->len = 0;
	list->end = 0;
	list->width = 0;
	list->height = 0;
	return (list);
}

int				load_textures(t_data_map *all)
{
	if (malloc_textures(all) == -1)
		return (-1);
	all->t_no->img = load_text_img(all, all->path_no, all->t_no);
	all->t_so->img = load_text_img(all, all->path_so, all->t_so);
	all->t_we->img = load_text_img(all, all->path_we, all->t_we);
	all->t_ea->img = load_text_img(all, all->path_ea, all->t_ea);
	all->t_spr->img = load_text_img(all, all->path_sprite, all->t_spr);
	if (!all->t_no->img || !all->t_so->img || !all->t_we->img
			|| !all->t_ea->img || !all->t_spr->img)
		return (errors_notify(7));
	all->t_no->addr_tex = (int *)load_text_addr(all->t_no);
	all->t_so->addr_tex = (int *)load_text_addr(all->t_so);
	all->t_we->addr_tex = (int *)load_text_addr(all->t_we);
	all->t_ea->addr_tex = (int *)load_text_addr(all->t_ea);
	all->t_spr->addr_tex = (int *)load_text_addr(all->t_spr);
	return (0);
}
