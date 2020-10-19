/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:50:56 by gbroccol          #+#    #+#             */
/*   Updated: 2020/10/06 17:50:58 by gbroccol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BUFFER_SIZE 32

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "./miniLibX/mlx.h"
# include "./libft/libft.h"

typedef struct			s_sprite {
	int					visible;
	int					x_2d;
	int					y_2d;
	int					x_3d;
	int					y_3d;
	int					h_of;
	int					v_of;
	float				dist;
	float				dir;
	float				size;
	struct s_sprite		*next;
}						t_sprite;

typedef struct			s_img {
	void				*img;
	char				*addr;
	int					*addr_tex;
	int					bpp;
	int					len;
	int					end;
	int					width;
	int					height;
}						t_img;

typedef struct			s_ray_cast {
	float				fov;
	float				pov;
	int					col;
	float				angle;
	float				dist_to_pp;
	float				h_dis;
	float				v_dis;
	float				offset_y;
	float				offset_x;
	float				hx;
	float				hy;
	float				vx;
	float				vy;
	int					grid_x;
	int					grid_y;
	float				x_tex;
	float				y_tex;
	char				wall_site;
	int					wall_str;
	int					color;
	int					wall_size;
	float				ray_distance;
	float				*dist_to_walls;
	int					spr_x;
	int					spr_y;
	float				spr_dist;
}						t_ray_cast;

typedef struct			s_map_er {
	int					status;
	char				*str;
	int					map_str;
	int					width;
	int					height;
	int					no;
	int					so;
	int					we;
	int					ea;
	int					spr;
	int					floor_color_er;
	int					ceiling_color_er;
	int					r;
	int					g;
	int					b;
	int					map_len;
}						t_map_er;

typedef struct			s_data_map {
	void				*mlx;
	void				*mlx_win;
	char				**map;
	int					argc;
	float				bl_w;
	float				bl_h;
	int					tmp_h;
	int					tmp_w;
	int					make_scr;
	int					px;
	int					py;
	int					win_w;
	int					win_h;
	int					win_w_max;
	int					win_h_max;
	char				*path_no;
	char				*path_so;
	char				*path_we;
	char				*path_ea;
	char				*path_sprite;
	int					floor_hex;
	int					ceiling_hex;
	int					map_w;
	int					map_h;
	char				**spr_map;
	int					flag;
	t_img				*img;
	t_img				*t_no;
	t_img				*t_so;
	t_img				*t_we;
	t_img				*t_ea;
	t_img				*t_spr;
	t_ray_cast			*ray_cast;
	t_sprite			*sprites;
	t_map_er			*mr;
}						t_data_map;

/*
**  parsing and errors
*/
int						check_argc_argv(int argc, char **argv);
int						mr(t_data_map *all, char *str);
int						parser_data(t_data_map *all, char *str, t_map_er *mr);
int						resolution(t_data_map *all, char *str, t_map_er *mr);
int						map_errors_check(t_data_map *map_feature, t_map_er *mr);
int						map_walls_check(t_data_map *all, t_map_er *mr);
int						rewrite_map(t_data_map *all);
int						map_walls_check(t_data_map *all, t_map_er *mr);
int						errors_notify(int code);
int						errors_notify2(int code);
int						load_extra_data(t_data_map *all, t_ray_cast *rc);
int						load_textures(t_data_map *all);
int						create_sprite_map(t_data_map *all);
int						parser_map(t_data_map *all, char *str, t_map_er *mr);
int						check_all_errors(t_data_map *all, t_map_er *mr);

/*
**  srcs
*/
t_img					*malloc_img_list(void);
int						clear_data(t_data_map *all);
int						get_next_line(int fd, char **line);
void					draw_column(t_data_map *all, t_ray_cast *rc, int x);
int						key_press(int key, t_data_map *all);
int						key_press_exit(t_data_map *all);
int						draw_screen(t_data_map *all);
void					ray_casting(t_data_map *all, t_ray_cast *rc);
void					pixel_put(t_img *data, int x, int y, int color);
int						get_clr(t_img *text, int x, int y, float line);
t_sprite				*find_sprite(t_sprite *lst, int y, int x);
void					get_sprite(t_data_map *all, t_sprite *sprite);
void					spr_handle(t_data_map *all, t_sprite *lst,
							t_ray_cast *rc);
int						make_screen(t_data_map *all);
int						free_all(t_data_map *all);
int						free_textures(t_data_map *all, int i);
int						malloc_textures(t_data_map *all);

#endif
