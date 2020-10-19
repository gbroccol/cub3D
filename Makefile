# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anastasiya <anastasiya@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/29 21:32:03 by anastasiya        #+#    #+#              #
#    Updated: 2020/05/20 12:27:44 by anastasiya       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cub3D
LIBFT_PATH 		= ./libft
MINILIBX_PATH   = ./miniLibX
SRCS 			= \
		./parsing/parser_data.c \
		./parsing/resolution.c \
		./parsing/check_argc_argv.c \
		./parsing/map_errors_check.c \
		./parsing/map_errors_check2.c \
		./parsing/map_walls_check.c \
		./parsing/map_read.c \
		./parsing/load_extra_data.c \
		./parsing/load_textures.c \
		./parsing/errors_notify.c \
		./parsing/malloc_textures.c \
		./parsing/create_sprite_map.c \
		./parsing/parser_map.c \
		./parsing/check_all_errors.c \
		./srcs/main.c \
		./srcs/get_next_line.c \
		./srcs/key_press.c \
		./srcs/ray_casting.c \
		./srcs/spr_handle.c \
		./srcs/get_sprite.c \
		./srcs/clear_data.c \
		./srcs/make_screen.c \
		./srcs/draw_column.c \
		./srcs/free_all.c
		
OBJS			= ${SRCS:.c=.o}
INCLUDE 		= cube3d.h
LIBFT 			= libft
MINILIBX 		= miniLibX
CC				= gcc -g -Wall -Wextra -Werror
RM				= rm -f
MLXFLAGS 		= -I ./miniLibX -L ./miniLibX -lmlx -framework OpenGl -framework Appkit
# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking

all:			libft_all minilibx_all ${NAME}
$(NAME):		${OBJS} 
				@$(CC) $(MLXFLAGS) $(LIBFLAGS) libmlx.dylib libft.a -I./ $(OBJS) -o $@ 
clean:			libft_clean minilibx_clean
				@${RM} ${OBJS}
fclean:			libft_fclean clean
				@${RM} ${NAME}
				$(RM) libmlx.dylib
				$(RM) screenshot.bmp

re:				fclean all

# make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command
libft_all:
	make -C $(LIBFT_PATH) all
	cp ./libft/libft.a libft.a

libft_clean:
	make -C $(LIBFT_PATH) clean

libft_fclean:
	make -C $(LIBFT_PATH) fclean
	$(RM) libft.a

minilibx_all:
	make -C $(MINILIBX_PATH) all
	cp ./minilibX/libmlx.dylib libmlx.dylib

minilibx_clean:
	make -C $(MINILIBX_PATH) clean

.PHONY: all fclean clean re