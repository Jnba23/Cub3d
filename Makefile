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

CFLAGS = -Wall -Werror -Wextra -g3 #-O3

MLX_FLAGS_FW = -L/Users/asayad/.brew/opt/glfw/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

SRCM = infile_pars.c infile_pars1.c infile_pars2.c infile_pars3.c infile_pars4.c infile_pars5.c pars_utils.c \
	pars_utils1.c get_next_line.c get_next_line_utils.c \

SRCF = $(addprefix srcs/, $(SRCM))

OBJM = $(SRCM:.c=.o)

OBJF = $(addprefix objs/, $(OBJM))

MLX = MLX42/libmlx42.a

INCS	= includes

INCMLX	= MLX42/include/MLX42/

SRCB 	= \

OBJB 	= \

NAME 	= cub3d

Header	= cub3d.h ./get_next_line/get_next_line.h

all: $(MLX) $(NAME)

$(MLX):
	@echo "$(BRED)Building MLX $(RESET)"
	@make -C MLX42 >/dev/null

$(NAME): $(OBJF)
	$(CC) $(CFLAGS) $(MLX)  $(MLX_FLAGS_FW) $^ -o $@


objs/%.o: srcs/%.c $(HEADER)
	mkdir -p objs
	$(CC) $(CFLAGS) -I$(INCS) -I$(INCMLX) -MMD $< -c -o $@

clean:
	rm -rf objs

fclean: clean
	make clean -C MLX42/
	rm -f $(NAME)

re: fclean all

-include $(DEPS)