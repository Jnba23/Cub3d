# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asayad <asayad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:03:43 by hmoukit           #+#    #+#              #
#    Updated: 2025/03/01 14:06:22 by asayad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Colors		#
BBLACK = \033[1;30m
BRED = \033[1;31m
BGREEN = \033[1;32m
BYELLOW = \033[1;33m
BBLUE = \033[1;34m
BPURPLE = \033[1;35m
BCYAN = \033[1;36m
BWHITE = \033[1;37m
DEPS	= $(OBJF:.o=.d)
CYAN	= \033[1;36m
RESET	= \033[0m
#	End			#

#/*Makefile*/#

CC = cc

CFLAGS = -Wall -Werror -Wextra -MMD -I$(INCS) -I$(INCMLX) -g3 -Ofast #-fsanitize=address

# MLX_FLAGS_FW = -L/usr/lib/x86_64-linux-gnu -lglfw -lm -ldl -pthread #linux -Wadoud
MLX_FLAGS_FW = -L/Users/asayad/.brew/opt/glfw/lib -lglfw -lm -framework Cocoa -framework OpenGL -framework IOKit #MAC-Wadoud
# MLX_FLAGS_FW = -L/Users/hmoukit/homebrew/opt/glfw/lib -lglfw -lm -framework Cocoa -framework OpenGL -framework IOKit #MAC-Hajar

PARSM = infile_pars.c infile_pars1.c infile_pars2.c infile_pars3.c infile_pars4.c infile_pars5.c pars_utils.c \
	infile_pars6.c infile_pars7.c infile_pars8.c infile_pars9.c pars_utils1.c pars_utils2.c get_next_line.c get_next_line_utils.c ft_split.c
GAMEM = game_init.c utils.c utils_2.c utils_3.c ray_casting.c cub3d.c rendering_3D.c movements.c intersections.c \
		textures.c textures_utils.c

PARSB = infile_pars_bonus.c infile_pars1_bonus.c infile_pars2_bonus.c infile_pars3_bonus.c infile_pars4_bonus.c infile_pars5_bonus.c \
		pars_utils_bonus.c pars_utils1_bonus.c pars_utils2_bonus.c get_next_line.c get_next_line_utils.c ft_split.c infile_pars6_bonus.c infile_pars7_bonus.c infile_pars8_bonus.c
GAMEB = animation_bonus.c cub3d_bonus.c draw_line_bonus.c game_init_bonus.c intersections_bonus.c mouse_bonus.c movements_bonus.c \
		ray_casting_bonus.c rendering_2D_bonus.c rendering_3D_bonus.c textures_bonus.c utils_bonus.c utils_2_bonus.c utils_3_bonus.c \
		update_move.c textures_drawing_bonus.c 2D_utils_bonus.c

PARSF = $(addprefix mandatory/parssing/, $(PARSM))
GAMEF = $(addprefix mandatory/game/, $(GAMEM))

PARSBO = $(addprefix bonus/parssing/, $(PARSB))
GAMEBO = $(addprefix bonus/game/, $(GAMEB))

OBJ_PARS_M = $(PARSF:.c=.o)
OBJ_GAME_M = $(GAMEF:.c=.o)

OBJ_PARS_B = $(PARSBO:.c=.o)
OBJ_GAME_B = $(GAMEBO:.c=.o)

OBJ_PARS_F = $(addprefix objs_man/, $(notdir $(OBJ_PARS_M)))
OBJ_GAME_F = $(addprefix objs_man/, $(notdir $(OBJ_GAME_M)))

OBJ_PARS_BO = $(addprefix objs_bon/, $(notdir $(OBJ_PARS_B)))
OBJ_GAME_BO = $(addprefix objs_bon/, $(notdir $(OBJ_GAME_B)))

MLX = MLX42/build/libmlx42.a

INCS	= includes

INCMLX	= MLX42/include/MLX42/

NAME 	= cub3D

HEADER_MAN	= ./includes/cub3d.h ./includes/get_next_line.h

BONUS	= cub3D_bonus

HEADER_BON	= ./includes/cub3d_bonus.h ./includes/get_next_line.h

all: $(MLX) $(NAME)

bonus: $(MLX) $(BONUS)

$(MLX):
	@echo "$(BRED)Building MLX $(RESET)"
	@cmake -B MLX42/build -S MLX42/ > /dev/null && make -C MLX42/build > /dev/null

$(NAME): $(OBJ_PARS_F) $(OBJ_GAME_F)
	$(CC) $(CFLAGS) $^ $(MLX)  $(MLX_FLAGS_FW) -o $@

objs_man/%.o: mandatory/parssing/%.c
	mkdir -p objs_man
	$(CC) $(CFLAGS) $< -c -o $@

objs_man/%.o: mandatory/game/%.c
	mkdir -p objs_man
	$(CC) $(CFLAGS) $< -c -o $@

$(BONUS): $(OBJ_PARS_BO) $(OBJ_GAME_BO)
	$(CC) $(CFLAGS) $^ $(MLX)  $(MLX_FLAGS_FW) -o $@

objs_bon/%.o: bonus/parssing/%.c
	mkdir -p objs_bon
	$(CC) $(CFLAGS) $< -c -o $@

objs_bon/%.o: bonus/game/%.c
	mkdir -p objs_bon
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	@rm -rf objs_man
	@rm -rf objs_bon

fclean: clean
	@if [ -f Makefile ]; then make clean -C MLX42/build; fi
	@rm -f $(NAME) $(BONUS)

re: fclean all bonus

-include objs_man/*.d objs_bon/*.d