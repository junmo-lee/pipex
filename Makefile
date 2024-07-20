.DEFAULT_GOAL := all

NAME	= pipex
NAME_B	= pipex_bonus

DEBUG_NAME = debug
DEBUG_NAME_B = debug_bonus

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft/

LDFLAGS	= -L$(LIBFT_DIR)
LDLIBS	= -lft

INC		= pipex.h
INC_B	= pipex_bonus.h

SRCS	= main.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c \
			utils.c read_file.c write_file.c \
			path_join.c pipex_init.c do_pipex.c 
			

SRCS_B	= main_bonus.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c \
			utils_bonus.c read_file_bonus.c write_file_bonus.c \
			path_join_bonus.c pipex_init_bonus.c do_pipex_bonus.c 

OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(SRCS_B:.c=.o)

DEF		= $(SRCS:.c=.d) 
DEF_B	= $(SRCS_B:.c=.d)
-include $(DEF) $(DEF_B)

ifdef DEBUG_FLAG
	CFLAGS += -g3 -fsanitize=address
endif

$(LIBFT) :
	make -C $(LIBFT_DIR) all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME) -I $(INC)


$(NAME_B): $(LIBFT) $(OBJS_B)
	cp $(LIBFT) $(NAME_B)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME_B) -I $(INC_B)

$(DEBUG_NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(DEBUG_NAME)
	$(CC) $(CFLAGS) $(CDEF) $^ -o $(DEBUG_NAME) -I $(INC) $(LIBS)

$(DEBUG_NAME_B): $(LIBFT) $(OBJS_B)
	cp $(LIBFT) $(DEBUG_NAME_B)
	$(CC) $(CFLAGS) $(CDEF) $^ -o $(DEBUG_NAME_B) -I $(INC_B) $(LIBS)

all : $(NAME)
bonus : $(NAME_B)

clean :
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(OBJS_B) $(DEF) $(DEF_B)

fclean :
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJS) $(OBJS_B) $(DEF) $(DEF_B) $(NAME) $(NAME_B)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re