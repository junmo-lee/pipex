.DEFAULT_GOAL := all

NAME	= pipex

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/

LDFLAGS	= -L$(LIBFT_DIR)
LDLIBS	= -lft

INC		= pipex.h
INC_B	= pipex_bonus.h

SRCS	= main.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c \
			utils.c read_file.c write_file.c pipex_split.c \
			path_join.c pipex_init.c do_pipex.c 

SRCS_B	= main_bonus.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c \
			utils_bonus.c read_file_bonus.c write_file_bonus.c pipex_split_bonus.c\
			path_join_bonus.c pipex_init_bonus.c do_pipex_bonus.c 

OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(SRCS_B:.c=.o)

$(LIBFT) :
	make -C $(LIBFT_DIR) all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

LAST_ALL: $(LIBFT) $(OBJS)
	rm -f LAST_BONUS
	cp $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME) -I $(INC)
	touch $@

LAST_BONUS: $(LIBFT) $(OBJS_B)
	rm -f LAST_ALL
	cp $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME) -I $(INC_B)
	touch $@

all: LAST_ALL
bonus: LAST_BONUS

clean :
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(OBJS_B)

fclean :
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJS) $(OBJS_B) $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re