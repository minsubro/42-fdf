CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/create_map.c		\
	   src/draw_line.c		\
	   src/draw.c			\
	   src/fdf_main.c		\
	   src/ft_atoi.c		\
	   src/get_next_line_bonus.c	\
	   src/get_next_line_utils_bonus.c	\
	   src/projection.c	\
	   src/key_input.c	\
	   src/list.c		\
	   src/make_arr.c	\
	   src/make_xy.c	\
	   src/position_setting.c	\
	   src/rotate.c				\
	   src/split.c				\
	   src/utils.c				\
	   src/same_line.c			


NAME = fdf
OBJS = $(SRCS:.c=.o)


RM = rm -f


all : $(NAME)


$(NAME) : $(OBJS) 
	$(CC) $^ -o $(NAME) -Lminilibx -lmlx -framework OpenGL -framework Appkit
 
%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re