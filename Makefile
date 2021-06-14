
.PHONY: all clean fclean re

NAME = scop
NAME_LIBFT = libft.a

LIBFT = $(addprefix $(LIBFT_DIR),$(NAME_LIBFT))

SRC_DIR = ./src/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
LFT = -L $(LIBFT_DIR) -lft

SRCS_LIST = main.c parse_obj_file.c mat4.c vec3.c create_shader.c parse_bmp.c
HEADERS_LIST = scop.h

SRCS = $(addprefix $(SRC_DIR),$(SRCS_LIST))

OBJS = $(SRCS:.c=.o)

INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)
OPENGL_INCLUDES =  -I/usr/local/Cellar/glfw/3.3.2/include
OPENGL_SOURCES =-framework OpenGl -framework Cocoa  -lglfw3 -framework CoreVideo -framework IOKit -lSOIL
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

%.o: %.c $(addprefix $(INC_DIR),$(HEADERS_LIST))
	@$(CC) $(CFLAGS) $(INCLUDES) $(OPENGL_INCLUDES) -o $@ -c $<
	@echo ".\c"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(LFT) $(INCLUDES) $(OPENGL_SOURCES) $(OPENGL_INCLUDES) $(OBJS) -o $(NAME)
	@echo "$(NAME_PS) executable created"

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@/bin/rm -f $(OBJS) $(OBJS) $(OBJS)
	@echo "Object files deleted"
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Executable files deleted"
	@make fclean -C $(LIBFT_DIR)

re: fclean all
