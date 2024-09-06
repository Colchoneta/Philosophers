NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

CFILES = main.c \
	initialization/check_arguments.c initialization/init_data.c \
	threads/action.c threads/print_message.c threads/start_thread.c threads/start_threads.c \
	utils/ft_atoi.c utils/ft_calloc.c utils/ft_error.c utils/ft_exit.c utils/ft_get_time.c \
	utils/ft_isdigit.c utils/ft_isspace.c utils/ft_strcmp.c utils/ft_usleep.c\

OBJECTS = $(CFILES:.c=.o)

all: libraries $(NAME)

%.o : %.c
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf $(UP)$(CUT)

libraries:
#	@echo $(B)
#	make -C $(LIBFT_PATH) all
#	@echo $(B)
#	make -C $(PRINTF_PATH) all

$(NAME): $(OBJECTS)
	@echo $(Y)Compiling [$(CFILES)]...$(X)
	@echo $(G)Finished [$(CFILES)]$(X)
	@echo
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(LIBFT_LIB) $(PRINTF_LIB) $(OBJECTS) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

clean:
#	@make -C $(LIBFT_PATH) clean
#	@make -C $(PRINTF_PATH) clean
	@rm -f $(OBJECTS)
	@echo $(R)Removed [$(OBJECTS)]$(X)
	@echo $(R)Removed libraries.o$(X)

fclean: clean
#	@make -C $(LIBFT_PATH) fclean
#	@make -C $(PRINTF_PATH) fclean
	@rm -f $(NAME)
	@echo $(R)Removed [$(NAME)]$(X)

re: fclean all

.PHONY: all clean fclean re
