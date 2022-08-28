CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = create_map.c		\
	   draw_line.c		\
	   draw.c			\
	   fdf_main.c		\
	   ft_atoi.c		\
	   get_next_line_bonus.c	\
	   get_next_line_utils_bonus.c	\
	   projection.c	\
	   key_input.c	\
	   list.c		\
	   make_arr.c	\
	   make_xy.c	\
	   position_setting.c	\
	   rotate.c				\
	   split.c				\
	   utils.c				\
	   same_line.c			


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