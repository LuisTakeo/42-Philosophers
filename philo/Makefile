CC = gcc
#-fsanitize=thread
FLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread

NAME = philo
SRC = ${addsuffix .c, main utils utils2 init actions monitor}
OBJS = ${SRC:%.c=bin/%.o}


all: initial_msg $(NAME)
	@echo "$(NAME): Será que estou compilado ou apenas existindo?"

initial_msg:
	@echo "$(NAME): Compilar ou não compilar? Eis a questão..."

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) && echo "Compilando: $@"

bin/%.o:%.c
	@$(CC) $(FLAGS) -o $@ -c $< && echo "Compilando: $(notdir $<)"

clean:
	@rm -f $(OBJS) && echo "$(NAME): Objects removidos"

fclean: clean
	@rm -f $(NAME) && echo "$(NAME): Executável removido"

re: fclean all
