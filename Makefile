NAME_PROGRAMM = philosophers

CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g -pthread

LIBFT_PATH  = lib/libft/
LIBFT       = $(LIBFT_PATH)libft.a
INCLUDES    = -I. -I$(LIBFT_PATH)

SRCS_PROGRAMM = src/main.c \
        src/parse/parse.c \
        src/philo/init_philos.c \
        src/philo/init_mutex.c \
        src/philo/philo_routine.c \
        src/philo/time.c

OBJS_PROGRAMM = $(SRCS_PROGRAMM:.c=.o)

all: $(NAME_PROGRAMM)

$(NAME_PROGRAMM): $(OBJS_PROGRAMM) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_PROGRAMM) $(LIBFT) $(INCLUDES) -o $(NAME_PROGRAMM)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJS_PROGRAMM) $(TEST_OBJS)
	make clean -C $(LIBFT_PATH)

fclean: clean
	rm -f $(NAME_PROGRAMM) test_philosophers
	make fclean -C $(LIBFT_PATH)

re: fclean all

TEST_SRCS = tests/test_philosophers.c \
        src/parse/parse.c \
        src/philo/init_philos.c \
        src/philo/init_mutex.c \
        src/philo/philo_routine.c \
        src/philo/time.c

TEST_OBJS = $(TEST_SRCS:.c=.o)

test: $(TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBFT) $(INCLUDES) -o test_philosophers
	./test_philosophers
