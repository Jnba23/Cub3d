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

CFLAGS = -Wall -Werror -Wextra -MMD -I$(INCS) -I$(INCMLX) -g3 -fsanitize=address,undefined

# MLX_FLAGS_FW = -L/Users/hmoukit/homebrew/opt/glfw/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit //MAC
MLX_FLAGS_FW = $(MLX) -L/usr/lib/x86_64-linux-gnu/ -ldl -lglfw -pthread -lm -lX11

PARSM = infile_pars.c infile_pars1.c infile_pars2.c infile_pars3.c infile_pars4.c infile_pars5.c pars_utils.c \
	pars_utils1.c get_next_line.c get_next_line_utils.c
GAMEM = game_init.c utils.c utils_2.c ray_casting.c cub3d.c rendering.c movements.c intersections.c draw_line.c

PARSF = $(addprefix srcs/parssing/, $(PARSM))
GAMEF = $(addprefix srcs/game/, $(GAMEM))

OBJ_PARS_M = $(PARSF:.c=.o)
OBJ_GAME_M = $(GAMEF:.c=.o)

OBJ_PARS_F = $(addprefix objs/, $(notdir $(OBJ_PARS_M)))
OBJ_GAME_F = $(addprefix objs/, $(notdir $(OBJ_GAME_M)))

MLX = MLX42/build/libmlx42.a

INCS	= includes

INCMLX	= MLX42/include/MLX42/

NAME 	= cub3d

HEADER	= cub3d.h ./get_next_line/get_next_line.h

all: $(MLX) $(NAME)

$(MLX):
	@echo "$(BRED)Building MLX $(RESET)"
	@make -C MLX42 >/dev/null

$(NAME): $(OBJ_PARS_F) $(OBJ_GAME_F)
	$(CC) -v $(CFLAGS) -o $@ $^ $(MLX_FLAGS_FW) $(MLX)
# $(CC) $(CFLAGS) $(MLX)  $(MLX_FLAGS_FW) $^ -o $@ //MAC

objs/%.o: srcs/parssing/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) $< -c -o $@

objs/%.o: srcs/game/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf objs

fclean: clean
	make clean -C MLX42/
	rm -f $(NAME)

re: fclean all

-include $(objs:.o=.d)