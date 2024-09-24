# ------------------ BASIC -----------------------

CC = cc

FLAGS = -Wall -Werror -Wextra

NAME=philo

# ------------------ PROJECT ---------------------

INCLUDES = -Iincludes/

SOURCES_DIR = sources/

SOURCES_FILES =	main.c\
		args.c\
		check_parameters.c\
		convert.c\
		message.c\
		monitor.c\
		philosopher.c\
		philosopher2.c\
		simulation.c\
		table.c\
		table2.c\
		time.c

OBJECTS_FILES = $(SOURCES_FILES:.c=.o)
DEPENDS_FILES = $(SOURCES_FILES:.c=.d)

SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCES_FILES))
OBJECTS = $(SOURCES:.c=.o)
DEPENDS = $(SOURCES:.c=.d)

all: $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) -pthread $(OBJECTS) -o $@

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(DEPENDS)

clean :
	rm -rf $(OBJECTS)
	rm -rf $(DEPENDS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

helgrind_count_eat : all
	valgrind --log-file=hellog --tool=helgrind --history-level=approx -s ./philo 3 800 200 100 3

helgrind_die : all
	valgrind --log-file=hellog --tool=helgrind --history-level=approx -s ./philo 6 300 200 100

helgrind_zero_eat:
	valgrind --log-file=hellog --tool=helgrind --history-level=approx -s ./philo 3 800 200 100 0

valgrind : all
	valgrind --show-leak-kinds=all --leak-check=full ./philo 3 200 200 100

valgrind_zero_eat : all
	valgrind --show-leak-kinds=all --leak-check=full ./philo 3 200 200 100 0

test_eating: all
	./philo 10 650 200 100 2 | grep "is eating" | cut -f1 -d" " --complement | sort


.PHONY: clean fclean re valgrind test_eating
