/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 19:40:37 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/04 19:40:41 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int				get_sr_color(t_data_map *all, int x, int y)
{
	char			*dst;

	dst = all->img->addr + (y * all->img->len + x * (all->img->bpp / 8));
	return (*(unsigned int*)dst);
}

static void				header(unsigned char *header_arr, int size,
								t_data_map *all, int temp)
{
	header_arr[0] = (unsigned char)'B';
	header_arr[1] = (unsigned char)'M';
	header_arr[2] = (unsigned char)size;
	header_arr[3] = (unsigned char)(size >> 8);
	header_arr[4] = (unsigned char)(size >> 16);
	header_arr[5] = (unsigned char)(size >> 24);
	header_arr[10] = (unsigned char)54;
	header_arr[14] = (unsigned char)40;
	header_arr[18] = (unsigned char)temp;
	header_arr[19] = (unsigned char)(temp >> 8);
	header_arr[20] = (unsigned char)(temp >> 16);
	header_arr[21] = (unsigned char)(temp >> 24);
	header_arr[22] = (unsigned char)all->win_h;
	header_arr[23] = (unsigned char)(all->win_h >> 8);
	header_arr[24] = (unsigned char)(all->win_h >> 16);
	header_arr[25] = (unsigned char)(all->win_h >> 24);
	header_arr[26] = (unsigned char)1;
	header_arr[28] = (unsigned char)24;
}

static void				screen(t_data_map *all, int fd, int res)
{
	int					color;
	int					x;
	int					y;
	int					size_x;

	color = 0;
	x = 0;
	y = all->win_h - 1;
	size_x = res;
	while (y >= 0)
	{
		while (x < size_x)
		{
			color = get_sr_color(all, x, y);
			write(fd, &color, 3);
			x++;
		}
		y--;
		x = 0;
	}
}

int						make_screen(t_data_map *all)
{
	int					fd;
	unsigned char		header_arr[54];
	int					count;
	int					size;
	int					temp_res;

	temp_res = all->win_w;
	if (all->win_w % 4)
		temp_res = all->win_w - (all->win_w % 4);
	size = temp_res * all->win_h + 54;
	count = 0;
	if ((fd = open("./screenshot.bmp", O_RDWR | O_CREAT, 0666)) < 0)
		return (-1);
	while (count < 54)
	{
		header_arr[count] = (unsigned char)0;
		count++;
	}
	header(header_arr, size, all, temp_res);
	write(fd, header_arr, 54);
	screen(all, fd, temp_res);
	close(fd);
	exit(0);
}
